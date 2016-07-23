#include <stdio.h>

struct DATE {
	int date;
	int year;
	int ie_data;
	int res_2;					/*			*/
	int res_3;					/*	保留位	*/
	int res_4; 					/*			*/
	char note[8*196];
	struct DATE *up;
	struct DATE *down;
};
extern date_of_today; 

void get_save_note(long int time,struct DATE *head){	/* time比如 1111 11月11日 */
	int i = 0,word_count = 0,chi_flag = 0;
	char buf[3] = {'\0'};
	struct DATE *temA = NULL;
	struct DATE *temB = NULL;

	temA = (struct DATE *)malloc(sizeof(struct DATE));
	temB = head;
	while ( temB->down != NULL )
		temB = temB->down;

	system("cls");
	date_display(2,2,0);
	line_ini(0,66);
	line_ini(1,0);
	gotoxy(1,7);
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	gotoxy(25,6); printf("Text Here ↓\n\n|");
	
	temA->date = date_of_today; 
	temA->year = date_of_today / 10000 ;
//	gotoxy(); 
	for (i=192;i<1568;i++,word_count++){
		temA->note[i] = getch();
		if (temA->note[i] >= 0xc0 && chi_flag == 0){
			chi_flag = 1;
			continue;
		}
		if (chi_flag){
			chi_flag = 0 ;
			buf[0] = temA->note[i-1];
			buf[1] = temA->note[i]; 
			printf("%s",buf); 
		}
		if (word_count >= 64){
			printf("\n|");
			word_count = 0 ;
		}
		printf("%c",temA->note[i]);
		if (temA->note[i] == 8) {
			printf(" ");
			putchar(8);
			i-=2;
		}
		if (temA->note[i] == -32){
			i -= 2;
		}
		if (temA->note[i] == 13){
			break;
		}
		if (temA->note[i] == 10){
			printf("|");
		}
	}
	temA->up = temB; 
	temA->down = NULL; 
	temB->down = temA;
/*
	gets(temA->note); 
*/

	printf("%s\n\n",&temA->note[192]);
	system("pause");
//	system("cls");

	if (temA->note[192] == 13) 
		return;

	FILE *fp_for_mp = NULL;
	fp_for_mp = fopen("BScheduleData","a");
	i = fwrite(temA,6,4,fp_for_mp);
	i = fwrite(temA->note,1568,1,fp_for_mp);
	fclose(fp_for_mp);

	if (i == 0){
		printf("\n\n write error!!!");
		system("pause");
	}

	system("cls");
}

void review_text(head){
	system("cls"); 
	gotoxy(0,29); 
	printf("press e to edit  i to input  ↑↓to chose ");
	getch();
	
	system("cls");
}

void money_plan_load_and_print(){
	char article[1024] = { '\0' };
	int flag = 0;
	FILE *fp_for_mp = NULL;

 
	flag ^= flag;
	flag = fread(article,1,1024,fp_for_mp);
	if (flag == 0) return;
	printf("%s\n",article);
	fclose(fp_for_mp);
}

