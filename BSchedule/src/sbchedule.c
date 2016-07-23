/* 
 * Main Funtion in BSchedule 
 * S~Bchedule.c 
 */
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <conio.h>
#include <time.h>

struct DATE {
	int year;
	int date;
	int ie_date;
	int res_2;					/*			*/
	int res_3;					/*	±£ÁôÎ»	*/
	int res_4; 					/*			*/
	char note[8*196];
	struct DATE *up;
	struct DATE *down;
};

extern ch[4];
extern char _num[10][5];
extern char _mon[12][4]; 
extern char _week[8][4];
extern struct DATE today;

char _ymd[3][5] = { {"year"},
					{" mon"},
					{" day"} };

int in_ymd[3] = {2015,12,13};
long int now_date = 20150101;

int Bchedule( struct DATE *head ){
	int i ,k;
	struct DATE *temA = NULL;
	char number_control = 0;
	temA = head->down;

	system("cls");
//	system("pause");
	while ( 1 ){
		gotoxy(0,29);
		printf("Esc : exit   Number : Chose Function");
		now_date = date_display(68,2,0);
		line_ini(1,66);
		
		gotoxy(68,8);
		for (i=0,number_control=8;i<=128;i){
			printf("%c",today.note[i+196]);
			if ( ++i % 32 == 0){
				k = 0; 
				while ( 1 ){
					if ( today.note[i++] == ' '){
						continue;
					} else 
						break;
				}
				gotoxy(68,++number_control);
			}
		}
		if ( today.note[i+1] != ' ' ){
			printf("........");
		}
		gotoxy(0,0);
		printf("    Bchedule .... \n");
		printf("                  \n");
		printf("    1,Calendar    \n");
		printf("    2,Note        \n");
		printf("    3,cAlc        \n");
		number_control ^= number_control;
		number_control = getch();
		if (number_control == '1' || number_control == 'c'){
			draw_calendar(now_date/10000,now_date);
			system("mode con cols=120 lines=30");
		} else if ( number_control == '2' || number_control == 'n' ){
			gotoxy(16,3);
			printf("* 1,edit today   ");
			gotoxy(16,4);
			printf("  2,edit certain day   ");
			gotoxy(16,5);
			printf("  3,review text \n");
			gotoxy(16,3);
			number_control = getch();
			if (number_control == '1'){
				get_save_note(20151225,time,head);			/* date of today */
			} else if (number_control == '2'){
				;
			} else if (number_control == '3'){
				review_text(head);
			}
		} else if (number_control == '3' || number_control == 'a'){
			calc();
		} else if (number_control == 27){				// ASCii 27 === Esc 
			return 0;
//			line_clr();
//			break;
		}
	}
}

int get_user_input_date(){
	int k;
	line_clr();
	for (k=0;k<3;){
		gotoxy(0,2);
		printf("      %s  \n",_ymd[k]);
		printf("w     %4d \n",in_ymd[k]-1);
		printf("--->  %4d \n",in_ymd[k]); 
		printf("s     %4d \n",in_ymd[k]+1);
		printf("      %4d \n",in_ymd[k]+2);
		
		ch[0] = getch();
		if (ch[0] == 'w' ){
			in_ymd[k]--;
		} else if (ch[0] == 's'){
			in_ymd[k]++;
		} else if (ch[0] == 13){
			k++;
		}
		ch[0] = '\0';
	}
	printf("\n\n %d %d %d",in_ymd[0],in_ymd[1],in_ymd[2]);///////
	return in_ymd[2] + in_ymd[1]*100 + in_ymd[0]*100*100;
}

void get_date_note(int in_date,struct DATE *head){
	int i,y = 8;
	struct DATE *temA = head->down;
	
	while (temA->down != NULL){
		if ( temA->date == in_date ){
			break;
		}
		temA = temA->down; 
	}
	
	i=0;
	while ( *(temA->note+i) != '\0' ){
		if ( *(temA->note+i) == 10 ){
			gotoxy(74,y++);
		}
		printf("%c",*(temA->note + i));
		i++;
	}
}

void line_ini(int flag,int x){
	int i;
	for (i=0;i<30;i++){
		gotoxy(x,i);
		printf("|");
		Sleep(1);
	}
	if (flag){
		printf("%d",now_date);
	}
	gotoxy(0,0);
}

void line_clr(){
	int i;
	gotoxy(0,2);
	for (i = 0 ; i <= 20 ; i++)
		printf("                                                      \n");
}

