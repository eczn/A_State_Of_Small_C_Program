#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

const 
char _cap[][5] = {  { 0x7,0x5,0x3,0x2,0x2 },
				    { 0x4,0x4,0x7,0x5,0x7 } };
const 
char _num[10][5] = {{ 0x7,0x5,0x5,0x5,0x7 },			// 0
					{ 0x1,0x1,0x1,0x1,0x1 },			// 1
					{ 0x7,0x1,0x7,0x4,0x7 },			// 2
					{ 0x7,0x1,0x3,0x1,0x7 },			// 3
					{ 0x5,0x5,0x7,0x1,0x1 },			// 4
					{ 0x7,0x4,0x7,0x1,0x7 },			// 5
					{ 0x7,0x4,0x7,0x5,0x7 },			// 6
					{ 0x7,0x1,0x1,0x1,0x1 },			// 7
					{ 0x7,0x5,0x7,0x5,0x7 },			// 8
					{ 0x7,0x5,0x7,0x1,0x3 } };			// 9
/* ��ָ�� */
const 					
char _mon[12][4] = {{"Jan"},{"Feb"},{"Mar"},
					{"Apr"},{"May"},{"Jun"},
					{"Jul"},{"Aug"},{"Sep"},
					{"Oct"},{"Nov"},{"Dec"} };
const 
char _week[8][4] = {{"NUL"},{"Mon"},
					{"Tue"},{"Wed"},
					{"Thu"},{"Fri"},
					{"Sat"},{"Sun"} };
/*
void get_time(){
	time_t nowtime;
	time(&nowtime);
	struct tm *timeinfo = localtime( &nowtime );
	
	time(&nowtime);
	timeinfo = localtime( &nowtime );
}
*/

void draw( int num,int x,int y){
	int i,j,temp;
	for (i=0;i<5;i++){
		temp = _num[num][i];
		gotoxy(x,y++);
		for (j=0;j<3;j++){
			if ( temp & 0x4 ){
				printf("��");
			} else {
				printf("  ");
			}
			temp = temp << 1;
//			Sleep(1);
		}
	}
}

int gotoxy(int x,int y){
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}

int date_display(int x,int y,int flag){
	long int week_time = 0,i=0,time_num = 0;
	char input;
	time_t nowtime;
	time(&nowtime);
	struct tm *timeinfo = localtime( &nowtime );

	time(&nowtime);
	timeinfo = localtime( &nowtime );
	week_time =  week_time + timeinfo->tm_year + 1900;
	week_time *= 100;
	week_time += timeinfo->tm_mon+1;
	week_time *= 100; 
	week_time += timeinfo->tm_mday; 
	
	if (flag) 
		return week_time; 
	
	gotoxy(x,y-2);
	printf("   Today");
	gotoxy(x,y-1);
	printf("   %s     %s",_mon[timeinfo->tm_mon],_week[get_week(week_time)]);
	while ( i<=1 ){
		draw( timeinfo->tm_mday % 10 , x+4*(1-i)*2,y);
		timeinfo->tm_mday /= 10;
		i++;
	}
	return week_time;
}

int get_week(long int time){
	int week = -1;
	int month,year,day; 
	day = time % 100 ;
	time /= 100;
	month = time % 100 ;
	time /= 100; 
	year = time % 10000; 

	if(month == 1 | month == 2){
		month += 12;
		--year;               
	}
	week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 -year / 100 +year / 400) % 7 + 1;
	return week; // ���-1Ϊ����
}

////////////////////////////////////////////////////////
/*            Code : Copyed from internet.            */
/*     copyright broken? connect me and delete it     */
/*****************      warning      ******************/
/*              line:39 system("pause");              */
/*             would not adapt to other OS            */
////////////////////////////////////////////////////////

long int f(int year,int month) {
	/*f(�꣬��)���꣭1������<3;����f(�꣬��)����*/
	if(month<3) return year-1;
	else return year;
}

long int g(int month) {
	/*g(��)���£�13������<3;����g(��)���£�1*/
	if(month<3) return month+13;
	else return month+1;
}

long int n(int year,int month,int day) {
	/*N=1461*f(�ꡢ��)/4+153*g(��)/5+��*/
	return 1461L*f(year,month)/4+153L*g(month)/5+day;
}

int w(int year,int month,int day) {
	/*w=(N-621049)%7(0<=w<7)*/
	return(int)((n(year,month,day)%7-621049L%7+7)%7);
}

int date[12][6][7];
int day_tbl[ ][12]={{31,28,31,30,31,30,31,31,30,31,30,31},
					{31,29,31,30,31,30,31,31,30,31,30,31}};

void draw_calendar(int year,int month,int now_date){
	int sw,leap,i,j,k,wd,day;
//	int year;/*��*/
	int now_month,now_day; 
	now_day = now_date % 100 ; 
	now_date %= 10000; 
	now_month = now_date / 100;
	char title[]="SUN MON TUE WED THU FRI SAT";

	//clrscr();
	system("cls");
	system("mode con cols=100 lines=42");
//	printf("mon %d  day %d\n",now_month,now_day);
//	printf("Please input the year whose calendar you want to know: ");/*������*/
//	scanf("%d%*c",&year);/*�������ֵ���ӹ�ֵ��Ļس�*/
	sw=w(year,1,1);
	
	leap = year%4 == 0 && year%100 || year%400 == 0;/*������*/

	for(i=0; i<12; i++)
		for(j=0; j<6; j++)
			for(k=0; k<7; k++)
				date[i][j][k]=0;/*���ڱ���0*/

	for(i=0; i<12; i++) /*һ��ʮ������*/
		for(wd=0,day=1; day<=day_tbl[leap][i]; day++) {
			/*����i��1�µ������������ڱ�*/
			date[i][wd][sw]=day;
			sw=++sw%7;/*ÿ�������죬��0��6����*/
			if(sw==0) wd++;/*���ڱ�ÿ����һ�У������쿪ʼ�µ�һ��*/
		}
		
	printf("\n|==================The Calendar of Year %d =====================|\n|",year);
	Sleep(5);
	for(i=0; i<6; i++) {
		/*�Ȳ����i+1�º͵�i+7�µ����������*/
		for(wd=0,k=0; k<7; k++) /*���ڱ�ĵ����������ڣ���wd!=0*/
			wd+=date[i][5][k]+date[i+6][5][k];
		wd=wd?6:5;
		printf("%2d  %s  %2d  %s |\n|",i+1,title,i+7,title);
		Sleep(5);
		for(j=0; j<wd; j++) {
			printf("   ");/*����ĸ��հ׷�*/
			
			/*����Ϊ��i+1�£�����Ϊ��i+7��*/
			for(k=0; k<7; k++){
				if(date[i][j][k]){
					if ( (i+1==now_month) && (now_day == date[i][j][k])){
						printf(" NOW");
					} else 
						printf("%4d",date[i][j][k]);
//					Sleep(5);
				} else {
					printf("    ");
//					Sleep(5);
				}
			}
			printf("     ");/*���ʮ���հ׷�*/
			for(k=0; k<7; k++)
				if(date[i+6][j][k]){
					if ((i+7==now_month) && (now_day == date[i+6][j][k])){
						printf(" NOW");
					} else 
						printf("%4d",date[i+6][j][k]);
				}
				else printf("    ");
			printf(" |\n|");
			Sleep(5);
		}
		/*scanf("%*c");/*����س������һ���µ�����*/
	}
	puts("===================Press any key to quit...======================|");

	getch();
}

