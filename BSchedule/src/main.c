#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <conio.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char ch[4] = { '\0' };
char command = '\0'; 

struct DATE {
	int year;
	int date;
	int ie_date;
	int res_2;					/*			*/
	int res_3;					/* reserved	*/
	int res_4; 					/*			*/
	char note[8*196];
	struct DATE *up;
	struct DATE *down;
} today;

int date_of_today;

int main(int argc, char *argv[]){
	int temp,i = 1;
	int seconds;
	struct DATE *head = NULL;
	struct DATE *temA = NULL;

	system("mode con cols=120 lines=30");
	head = (struct DATE *)malloc(sizeof(struct DATE));
	head->up = NULL;
	head->down = NULL;
	load( head );
	save( head );
	temA = head->down; 

	date_of_today = date_display(0,0,1);
	FILE *fp_previou = NULL; 
	fp_previou = fopen("BScheduleData","r");
	if (fp_previou == NULL) 
		goto start; 
	while ( i != 0 ){
		i = fread(&temp,4,1,fp_previou);
		if (temp == date_of_today){
			today.year = 2016; 
			fread(&today.ie_date,4,4,fp_previou);
			fread(&today.note,1,8*196,fp_previou);
			break;
		}
//		system("pause");
	}
	
start:
//	while (1) {
//		command = 's'; 
//		date_display(68,2);
//		line_ini(0);
//		command = memu("eczn");
//		if ( command == 's' ) {
	Bchedule( head );	
//		} else if ( command == 'q' ){
//			break; 
//		}
//	}
//	printf("%d\n",temA->year);
//	printf("%s",temA->note[0]);
	 
//	command = memu("eczn");
	
	
	
//	printf("%c",command);
//	get_save_note();
//	date_display(64,5);
	
	return 0;
}



