#include<stdio.h>

int calc(){
	int term,result,flag = 0,end = 0;
	char ch;
	ini_calc_area(); 
	gotoxy(0,28); 
	scanf("%d",&result);					/* scanf���������һ���س�		*/
	do {									/* �ܶ�������Ϊȱ��				*/
		ch=getchar();						/* ���ǲ��ǣ���Ϊ����س��� 	*/
	} while ( ch == ' ' ) ;					/* ����Ӧ���൱���ַ�����ĩβ 	*/
	scanf("%d",&term);						/* ��'\0' ������ǽ���(����) 	*/

	while ( 1 ){          					/* ���ĸ����������� */
		if ( ch == '+' ){
			result = result + term;
		}
		else if ( ch == '-' ) {           
			result = result - term;
		}
		else if ( ch == '/' ){
			result = result / term; 
		}
		else if ( ch == '*' || ch == 'x' ){
			result = result * term; 
		}
		do {								/* ѭ����ȡ�������ֱ�����ǿո� */
			ch = getchar();	
		} while ( ch == ' ' );
		if (ch == '\n'){					/* ������� �س��� ���� */
			break;
		}
		flag = scanf("%d",&term);
    }
    gotoxy(0,27);
	printf("result: %d",result);
	return result;
}

void ini_calc_area(){						/* ����������,�ÿո񸲸� */
	gotoxy(0,27);
	printf("                                        \n                                             ");
}

