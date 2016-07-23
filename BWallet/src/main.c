#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define   ie_len	32				/* 20 + 12  (reserved) */
									/* int main_time,sec,min,hour. */
struct Btime {
	int main_time;
	int sec;
	int min;
	int hour;
};
struct iedata {
	int ie; 
	int date;
	struct iedata *up;
	struct iedata *down;
};

char command = 'd';
void memu(const char* user_name,char * command);
void memu_for_BBOX(const char* user_name,char * command);
void command_process(char command);
int now_time(struct Btime * Btm);

char user_exist = 0;
char user_name[16] = {'\0'};

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	struct iedata *head;
	struct iedata *temA;
	struct iedata *temB;
	int recently = -2;
	head = (struct iedata *) malloc( sizeof(struct iedata) );
	temA = (struct iedata *) malloc( sizeof(struct iedata) );
	head -> down = temA;
	head -> up   = NULL;
	temA -> down = NULL;
	temA -> up   = head; 

	system("cls");
	
	first_enter(user_name,&user_exist);
	
	while ( 1 ){
		memu(user_name,&command);
		command_process(command);
		if (command == 'g'){
			load_ie(head);
			draw_ie(head,recently);
		}
		if (command == 'a'){
			write_ie( head ,0,0,0);
		}
		if (command == 'm'){
			ie_manger(head);
			continue;
		}
		if (command == 'w'){
			gotoxy(0,8);
			money_plan_get_and_save();
		}
		if (command == 'q'){
			break;
		}
		if (command == 'b'){
			memu_for_BBOX(NULL,&command);
		}
	}
	system("cls");
	return 0;
}

void command_process(char command){
	
}

int now_time(struct Btime * Btm){
	int date;
	time_t nowtime;
	time(&nowtime); 
	struct tm *timeinfo = localtime( &nowtime );
			
	date =  (timeinfo->tm_year+1900)*10000 + 
				(timeinfo->tm_mon+1)*  100 + 
				 (timeinfo->tm_mday)*    1 ;
	 
	Btm->main_time = date;
	Btm->sec = timeinfo->tm_sec;
	Btm->hour = timeinfo->tm_hour;
	Btm->min = timeinfo->tm_min;
	
	return 0;
}

void write_ie(struct iedata *head,char switch_for_manger,int iee,int datee){
	/* ini */
	struct Btime *Btm = NULL;
	int voidvoid[8] = { 0 };
	Btm = (struct Btime *)malloc(sizeof(struct Btime));
	struct iedata *temA;
	struct iedata *temB;
	FILE *fp = NULL;
	int ie,date;
	
	now_time(Btm);
	/* 's' for manager */
	if (switch_for_manger) {
		fp = fopen("BWalletSave","a+");
		ie = iee,date = datee;
		goto s;
	}
	system("cls");
	fp = fopen("BWalletSave","a+");
	gotoxy(0,0);
	printf("_________________________________________________\n");
	printf("     input i&e, such as -50 : ");
	scanf("%d",&ie);
s:	
	fwrite(&ie,4,1,fp);
	if (switch_for_manger == 0)
		date = Btm->main_time;
	fwrite(&date,4,1,fp);
	fwrite( voidvoid ,4, 8-2 ,fp);
	
	fclose(fp);
	system("cls");
}

void load_ie(struct iedata *head){
	/* ini */
	struct iedata *temA;
	struct iedata *temB;

	int buffer[8];
	int EOF_flag = 1;
	FILE *fp;
	fp = fopen("BWalletSave","r+");
//	fread(&user_exist,1,1,fp);
//	fread(user_name,1,8,fp);
	/* load in order of List with buffer[] */
	temA = head;
	while ( EOF_flag != 0 ){
		EOF_flag = fread(buffer,4,8,fp);
		temB = (struct iedata *)malloc( sizeof(struct iedata) );
		temB->ie = buffer[0];
		temB->date = buffer[1];
		temB->up = temA;
		temB->down = NULL;
		temA->down = temB;
		temA = temB;
	}
	fclose(fp);
}

void draw_ie(struct iedata *head,int recent){
	/* ini */
	struct Btime *Btm = NULL;
	Btm = (struct Btime *)malloc(sizeof(struct Btime));
	struct iedata *temA = NULL;
	int sum = 0;
	int buffer[8];
	int recently;
	recently = recent;
	char_buffer_cls();
	gotoxy(0,8);
	printf("_________________________________________________\n");
	now_time(Btm);
	printf("            ie        date      ");
	printf("%d %d:%d\n",Btm->main_time,Btm->hour,Btm->min);
	
	/* draw in order of List */
	temA = head->down;
	while (temA->down != NULL && (recently >= 0 || recently == -2)){
		printf("         %5d  %10d\n",temA->ie,temA->date);
		sum = sum + temA->ie;
		temA = temA->down;
		if (recently != -2)
			recently--;
	}
	printf("_________________________________________________\n");
		printf("     SUM = %d  ",sum);
	/* Funtion Return */
	getch();
	gotoxy(0,0);
}

void char_buffer_cls(){
	int j; 
	gotoxy(0,8);
	for (j=0;j<12;j++)
		printf("                                                      \n");
}

void first_enter(const char *user_name,char *user_exist){
	int len = 0;
	FILE *fp = NULL; 
	fp = fopen("user.conf","r");
	len = fread(user_exist,1,1,fp);

		if (*user_exist == 0){
			printf("   hello,this program is designed to manger your money as his name\n");
			printf("   and the word 'ie' means 收支这两个字 I是收入 E是支出");
			gotoxy(3,2);
			printf("press your name:\n   ");
			gets(user_name);
			fclose(fp);
			fp = fopen("user.conf","w+");
			*user_exist = 1;
			fwrite(user_exist,1,1,fp);
			fwrite(user_name,1,16,fp);
		} else {
			fread(user_name,1,16,fp);
		}
	fclose(fp);
	system("cls");
}
