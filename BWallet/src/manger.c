#include <stdio.h>
#include <conio.h>
#include <time.h>
#define   ie_len	32

char ch[4] = { '\0' };
int ie_arr[256][8];

struct iedata {
	int ie; 
	int date;
	struct iedata *up;
	struct iedata *down;
};

void ie_manger(struct iedata *head){
	struct iedata *temA = NULL;
	struct iedata *temB = NULL;
	int cont = 0;
	int i = 0;
	int flag = 1;
	FILE *fp = NULL;
	load_ie(head);
	ini_ie_arr(head);
	
	system("cls");
	while (1){
		printf("     NO       I&E        date \n");
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		if (kbhit()){
			ch[0] = getch();
			if (ch[0] == -32)
				ch[1] = getch();
		}
		
		if (ch[0] != -32){
			if (ch[0] == 's'){
				cont++;
			}
			if (ch[0] == 'w'){
				cont--;
			}
			if (ch[0] == 27) {
				ch[0] = 0;
				break;
			}
			if (cont < 0) 
				cont = 0;
			ch[0] = 0;
		}
		else {
			if (ch[1] == 83) {
				del_action(cont);
				ch[1] = 0;
			}
			if (ch[1] == 72){
				cont--;
			}
			if (ch[1] == 80){
				cont++;
			}
			ch[1] = 0;
		}
		draw( cont );
		gotoxy(3,3);
		printf("¡ú");
		_sleep(200);
		system("cls"); 
	}

	remove("BWalletSave");
	for ( i=0 ; i<255 ; i++ ){
		if (ie_arr[i][1] == 0) break;
		write_ie(head,flag,ie_arr[i][0],ie_arr[i][1]);		//flag = 1;
	}
}

void ini_ie_arr(struct iedata *head){
	struct iedata *temA = NULL;
	int i = 0;
	temA = head->down;
	while (temA->down != NULL){
		ie_arr[i][0] = temA->ie;
		ie_arr[i][1] = temA->date;
		i++;
		if (i==255){
			printf("ÏîÄ¿Òç³öerror£¡");
			break;
		}
		temA = temA->down;
	}
}

/*
int new_input(int cont){
	if (kbhit()){
		ch[0] = getch();
		if (ch[0] == -32)
			ch[1] = getch();
	}
	if (ch[0] != -32){
		if (ch[0] == 's') cont++;
		if (ch[0] == 'w') cont--;	
	}
	else {
		if (ch[1] == 83) del_action(cont);
	}
	return 0;
}*/

void del_action(int cont){
	int i = cont;
	ie_arr[cont][0] = 0;
	ie_arr[cont][1] = 0;

	for (;i<255;i++){
		if (ie_arr[i][0] == 0 && ie_arr[i][1] == 0){
			ie_arr[i][0] = ie_arr[i+1][0];	
			ie_arr[i][1] = ie_arr[i+1][1];
			ie_arr[i+1][0] = 0;
			ie_arr[i+1][1] = 0;
		}
	}
}

void draw(int cont){
	if (cont >= 1){
		gotoxy(3,2);
		printf("         %5d  %10d",ie_arr[cont-1][0],ie_arr[cont-1][1]);
	}
	gotoxy(3,3);
	printf("         %5d  %10d",ie_arr[cont][0],ie_arr[cont][1]);
	gotoxy(3,4);	
	printf("         %5d  %10d",ie_arr[cont+1][0],ie_arr[cont+1][1]);
	gotoxy(3,5);
	printf("         %5d  %10d",ie_arr[cont+2][0],ie_arr[cont+2][1]);	
	gotoxy(5,3); printf("%2d",cont);
	gotoxy(0,7); money_plan_load_and_print();
}

