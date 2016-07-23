
#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_LAB 100
#define LAB_LEN 10
#define FOR_NEST 25
#define SUB_NEST 25
#define PROG_SIZE 10000
#define DELIMITER 1
#define VARIABLE 2
#define NUMBER 3
#define COMMAND 4
#define STRING 5
#define QUOTE 6

#define PRINT 1
#define INPUT 2
#define IF 3
#define THEN 4
#define FOR 5
#define NEXT 6
#define TO 7
#define GOTO 8
#define EOL 9
#define FINISHED 10
#define GOSUB 11
#define RETURN 12
#define END 13

char *prog;      /* holds expression to be analyzed  */
jmp_buf e_buf;   /* hold environment for longjmp() */

int variables[26]= {  /* 26 user variables,A-Z  */
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

struct commands { /* keyword lookup table  */
    char command[20];
    char tok;
} table[] = {  /* command must be entered lowercase  */
    "print",PRINT,   /* in this table  */
    "input",INPUT,
    "if",IF,
    "then",THEN,
    "goto",GOTO,
    "for",FOR,
    "next",NEXT,
    "to",TO,
    "gosub",GOSUB,
    "return",RETURN,
    "end",END,
    NULL,END
};

char token[80];     //ע��token����������
char token_type,tok;

struct label {
    char name [LAB_LEN];
    char *p;    /* point to place to go in source */
};

struct label label_table[NUM_LAB];
char *find_label(),*gpop();

struct for_stack {
    int var;   /* counter variable  */
    int target;  /* target value  */
    char *loc;
} fstack[FOR_NEST];  /* stack for FOR/NEXT loop  */
struct for_stack fpop();

char *gstack[SUB_NEST];  /* stack for gosub  */
int ftos;  /* index to top of FOR stack  */
int gtos;  /* index to top of GOSUB  */

void print(),scan_labels(),find_eol(),exec_goto();
void gosub(),greturn(),gpush(),label_init(),fpush();

/* Load a program */
load_program (char *p,char *fname)
{
    FILE *fp;
    int i=0;
   
    if (!(fp=fopen(fname,"rb")))  return 0;

    i=0;
    do  {
        *p = getc(fp);
        p++;i++;
    } while (!feof(fp)&&i<PROG_SIZE);
    *(p-2) = '/0';   /* null terminate the program  */
    fclose (fp);
    return 1;
}


/* ��������ֵ  ���� a��3  
 * ע������Ϊ�˼���������ǵı���������Ϊ26����ĸ
 */
assignment()
{
    int var,value;

    /* getthe variable name */
    get_token();
    if (!isalpha(*token))  //��Ϊ������������ĸ���� ���Աض�����ĸ����
    {
        serror(4);
        return;
    }

    var = toupper(*token)-'A';  //ת��Ϊ��д��ĸ  Ȼ���ȥ'A' �����ñ�����hash������������ ����A��ȥAΪ0 ����A�ַ������ڱ���hash���е�һ��λ��

    /* get the equals sign 
     * ��������ȡa=3 �м�ĵȺ�*/
    get_token();
    if (*token!='=')    //��Ȼ��ֵô �϶��еȺ���
    {
        serror(3);
        return;
    }

    /* a=3  �Ⱥ�ȡ���� ������ȡ��ֵ  */
    get_exp(&value);
   
    /* ������ȡ���ı��� ����a ֵΪ3 �����hash���� */
    variables[var] = value;
}


/* execute a simple version of the BASIC PRINT statement 
 * ִ�д�ӡ  �������ǻ��Ǿ���˵��*/
void print()
{
    int answer;
    int len=0,spaces;
    char last_delim;
   
    do  {
        get_token();  /* get next list item */
        if (tok==EOL||tok==FINISHED)  break;  //���ȡ���ķ�����һ�н��������ļ�����  ��Ȼ�Ĵ�ӡ����

                 
        //BASIC ��printһ���������÷�  �ڶ��־���print "hello world"  ��ӡ�ַ���  
        if (token_type==QUOTE)  
        {  
            printf ("%s",token);
            len+=strlen(token);
            get_token();    //ע�����Ǵ�ӡ�˺���ȡ��һ�η���
        }
        else   //��ӡ������
        { 
            putback();
            get_exp(&answer);
            get_token();    //ע�����Ǵ�ӡ�˺���ȡ��һ�η���
            len += printf ("%d",answer);
        }
        last_delim = *token;    
        
        
        /* Basic �����ִ�ӡ�����ʶ 
         * ���� print a,b ��ʾ����׼��ʽ��ӡ
         * ��print a;b ��ʾ���ս��ո�ʽ��ӡ  
         * ��ν��׼��ʽ���������Ǽ������  ������Ȼ���С���  
         */
        if (*token==',')  
        {
            /* compute number of move to next tab */
            spaces = 8-(len%8);
            len += spaces;  /* add in the tabbing position */
            while (spaces)  {
                printf (" ");
                spaces--;
            }
        }
        else if (*token==';')  
            printf ("  ");
        else if (tok != EOL && tok != FINISHED) serror (0);     //print a,b ����һ�κ� Ҫô�Ƕ��š��ֺ� Ҫô�����н��������ļ�����  ������߲�����һ  ��Ȼ����
    } while (*token==';'||*token==',');     //���� print a,b,c ���token�Ƕ��š��ֺ� ��ô��ʾ���滹�д�ӡ  ������

    /* �������н��������ļ�����  ��ôǰһ�ηֽ��������;����,  
     * ʾ�� ��� "print a," ����������﷨���� a���治Ӧ��Ҫ����
     * ��ô��ӡ��aȡ��token�Ƕ���  ���Ǹ�ֵ��last_delim ����ѭ��
     *  ��һ�����н���  ������ӡ���Ǽ����last_delim�Ƕ���  ���� */
    if (tok==EOL||tok==FINISHED)    
    {
        if (last_delim != ';' && last_delim != ',') printf ("/n");
    }
    else serror(0);  /* error is not, or ; */
}


/* �������б�ǩ 
 * �����������˵��basic�����Ԥ����  
 * ��������Դ���� �ҳ�����ı�ǩ  ��������ǩ��
 * ��ν��ǩlabel ��ʵC����Ҳ�� ����һ�㲻���� ��Ϊlabel����gotoһ����ֵ�  ���ڽṹ����������� goto���ֱ�����Ϊ�Ǿ��Բ��ܵ�
 * �����ں���gotoȴ�ǳ�������
 * ��������������������жϱ�ǩ���������� ��������Ϊ����  Ҫ֪�������ǩ���Ƕ�������Ϊ���ֵ�
 * ������ΰѱ�ǩ����ͨ��ֵ�ֿ���?
 */
void scan_labels()
{
    int addr;
    char *temp;

    label_init();  /* zero all labels */
    temp = prog;  /* save poiter to top of program */

    /* ���Դ�����е�һ���Ǹ����ֵĻ�  �����ǩ����  ����˵ʵ��   ��û���������ʲô����*/
    get_token();
    if (token_type==NUMBER)  
    {
        strcpy (label_table[0].name,token);
        label_table[0].p=prog;
    }
   
    find_eol();     //����
    do  {
        get_token();
        if (token_type==NUMBER)     //���������   ������һ�п�ͷ  ��ͷ�����ֲ�������һ����ֵ  
        {
            addr = get_next_label(token);
            if (addr==-1||addr==-2)  
            {
                (addr==-1) ? serror(5):serror(6);
            }
            strcpy (label_table[addr].name,token);
            label_table[addr].p = prog;  /* current point in program */
        }
        /* if not on a blank line , find next line */
        if (tok!=EOL) find_eol();
    } while (tok!=FINISHED);
    prog = temp;  /* restore to original */
}


/* find the start of next line */
void find_eol()
{
    while (*prog!='/n'&&*prog!='/0')  ++prog;
    if (*prog)  prog++;
}


/* return index of next free posion in the label array
      -1 is returned if the array is full.
      -2 is returned when duplicate label is found.
*/
get_next_label(char *s)
{
    register int t;

    for (t=0;t<NUM_LAB;++t) {
        if (label_table[t].name[0]==0)  return t;
        if (!strcmp(label_table[t].name,s)) return -2;  /* dup */
    }
    return -1;
}

/* find location of given label. A null is returned if
   label is not found; ohtherwise a pointer to the position
   of the label is returned.
*/
char *find_label(char *s)
{
    register int t;

    for (t=0;t<NUM_LAB;++t)
        if (!strcmp(label_table[t].name,s))  return label_table[t].p;
    return '/0';  /* error condition */
}


/* execute a GOTO statement. 
 * gotoһ����ʽ���� goto label 
 */
void exec_goto()
{
    char *loc;

    get_token();  /* �����ȡ��ţ����Ǳ�ǩ���� */
    
    loc = find_label (token);  //��ǩ��Ϊ��ת���ã����Ի�ȡ��ǩ����������Ҫ��취�õ���ǩ��������ַ
    if (loc=='/0')
        serror(7);  /* ���� */
    else prog=loc;  /* ���� ����progָ��  ָ������һ���������еĵ�ַ  ���ǵ���ȫ������*/
}


/* initialize the array that holds the labels.
   by convention , a null label name indicates that
   array posiiton is unused.
*/
void label_init()
{
    register int t;

    for (t=0;t<NUM_LAB;++t)  label_table[t].name[0]='/0';
}


/* execute an IF statement 
 * ִ��if���
 */
void exec_if()
{
    int x,y,cond;
    char op;
    /* ��������ֻ�Ǵ���һ���򵥵�if  ����if (x operator y) */
    get_exp(&x);  /* ��ȡ�����������ֵ */

    get_token();  /* ��ȡ������  "�ȽϷ�" */
    if (!strcmp("<>",*token))   //�����е������  һ���ַ��������ܸ�һ���ַ��Ƚϰ�
    {
        serror(0);  /* not a leagal oprator */
        return;
    }
    op = *token;
    get_exp(&y);  /* �������ұ�  */

    /* determine the outcome */
    cond = 0;
    switch(op)  {
        case '<':
            if (x<y) cond=1;
            break;
        case '>':
            if (x>y) cond=1;
            break;
        case '==':      //����Ҳ���е�����⣬op���ַ����� ��ô����ܻ���'=='�����Һ�Ц����basicû���������
            if (x==y) cond=1;
            break;
    }
    if (cond)  {  /* is true so process target of IF */
        get_token();
        if (tok != THEN)  {     //if ���������then ������ifûthen�Ǵ����
            serror(8);
            return;
        }  /* else program execution starts on next line */
    }
    else find_eol();  /* find start of next line */
}


/* execute a FOR loop
 * for ѭ��  ����Ҫ��ʽ ���µ�һƪ�Ѿ�����  
 * for i=1 to 10
 * next i
 * ��������ô�����
 */
void exec_for()
{
    struct for_stack i;     //����һ��ջԪ��  ��ʱ�����
    int value;

    get_token();  /*  ��ȡ���  �����ȡ������i */
    if (!isalpha(*token))  //�����ض����ַ���
    {
        serror(4);
        return;
    }

    i.var = toupper(*token) - 'A';  /* �����ǰѱ�������hash���е�  �������������������hash����λ��   */

    get_token();  /* ����õ��˵Ⱥ� */
    if (*token!='=')  
    {
        serror(3);
        return;
    }
    get_exp(&value);  /* ��ʼֵ  ����������1 */

    variables[i.var]=value;     //����ѳ�ʼֵ���ڱ���������

    get_token();

    if (tok != TO) serror(9);  /* ��ȡto���� */
    get_exp(&i.target);  /* ȡ������Ҫ�ﵽ����ֵ  ����������10 */

    /* if loop can execute at least once, push into on stack */
    if (value<=i.target)  {
        i.loc = prog;       //��¼Ҫִ�е����  ������forѭ��������Ҫִ�е����
        fpush(i);       //ѹջ
    }
    else  /* otherwise, skip loop code altogether */
        while (tok!=NEXT)  get_token();     //ÿ��next֮ǰ  ������forѭ��Ҫִ�е����   ����һֱִ��
}


/* execute a NEXT statement */
void next()
{
    struct for_stack i;

    i = fpop();  /*read the loop info */

    variables[i.var]++;  /* increment control variable */
    if (variables[i.var]>i.target)  return;  /* all done */
    fpush(i);   /* otherwise,return the info */
    prog = i.loc;  /* loop */
}


/* push function for the FOR stack */
void fpush(struct for_stack i)
{
    if (ftos>FOR_NEST)
    serror(10);
    fstack[ftos]=i;
    ftos++;
}


struct for_stack fpop()
{
    ftos--;
    if (ftos<0)  serror(11);
    return (fstack[ftos]);
}


/* exec a simple form of BASIC INPUT command */
void input()
{
    char str[80],var;
    int i;

    get_token();  /* see if prompt string id=s present */
    if (token_type == QUOTE)  {
        printf (token);  /* if so , print it and check for command */
        get_token();
        if (*token != ',')  serror(1);
        get_token();
    }
    else printf ("? ");  /* otherwise, prompt with / */
    var = toupper(*token) - 'A';  /* get the input var */

    scanf ("%d",&i);  /* read input */
    variables[var] = i;  /* store it */
}


/* execute a GOSUB command 
 * �������c�����еĺ������� */
void gosub()
{
    char *loc;

    get_token();
    /* find the label to call */
    loc = find_label(token);
    if (loc=='/0')
        serror(7);  /* label not defined */
    else  
    {
        gpush(prog);  /* ��ǰִ�еĵ�ַѹջ */
        prog = loc;  /* ���°�Ҫִ�еĵ�ַ��ֵ��prog */
    }
}


/* return from GOSUB */
void greturn()
{
    prog = gpop();
}


/* GOSUB stack push function */
void gpush(char *s)
{
    gtos++;

    if (gtos==SUB_NEST)  
    {
        serror(12);
        return;
    }

    gstack[gtos] = s;
}


/* GOSUB stack pop function */
char *gpop()
{
    if (gtos==0)  {
        serror(13);
        return 0;
    }
    return gstack[gtos--];
}

main (int argc,char *argv[])
{
    char in[80];
    int answer;
    char *p_buf;
    char *t;

    if (argc!=2)  {
        printf ("usage: run <filename>/n");
        exit (1);
    }

    /* allocate memory for the program */
    if (!(p_buf=(char *)malloc(PROG_SIZE)))  {
        printf ("allocation failure");
        exit (1);
    }

    /* load the program to execute */
    if (!load_program(p_buf,argv[1]))  exit(1);

    if (setjmp(e_buf))  exit(1); /* initialize the long jump */

    prog = p_buf;
    scan_labels();  /*  �������еı�ǩ  */
    ftos = 0;  /* ��ʼ��ջ  �����Ϊforѭ����׼����  */
    gtos = 0;  /* ��ʼ��ջ  �����Ϊgosub��׼���� */
    do  {
        token_type = get_token();
        /* �����ǰ�Ǳ��� */
        if (token_type==VARIABLE)  {
            putback();  /* ����progָ�뵽����ǰ */
            assignment();  /* ��ֵ  */
        }
        else  /* ���˱����Ǿ��ǹؼ�����  ������ͬѧ����  ��  �Ǹ�����һ��������ôû����  ������һ��������ô�ᵥ������ */
            switch (tok)  {
                case PRINT:
                    print();
                    break;
                case GOTO:
                    exec_goto();
                    break;
                case IF:
                    exec_if();
                    break;
                case FOR:
                    exec_for();
                    break;
                case NEXT:
                    next();
                    break;
                case INPUT:
                    input();
                    break;
                case GOSUB:
                    gosub();
                    break;
                case RETURN:
                    greturn();
                    break;
                case END:
                    exit(0);
            }
    }while (tok != FINISHED);
}
