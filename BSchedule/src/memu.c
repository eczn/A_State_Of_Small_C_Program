/* 欢迎界面233 */
//#include <windows.h>
//#define inix	5
//#define iniy	2
//#define extra_speed 75
/*
char shaonv[sizeof("          少女祈祷中。。。                 ")] = "           少女祈祷中。。。                 ";
int  ctrl = 0;
extern char ch[4];
char cont;
*/
/*
char memu(const char* user_name){
	int i = 0;
	int restart = 0;
	
	while (1) {
		printf("     hello~~  %s,",user_name);
		printf(" Welcome to BSchedule. press s&w to move '*'\n");
		printf("123456789012345678901234567890123456789012345678901234567890124");
		cprint("BSchedule .......................... SBchedule!",1-1,1);
		cprint("BWallet ............................ BWallet!!!",2-1,1);
		cprint(" ............................................. ",3-1,1);
		cprint("Setting ............................ Setting   ",4-1,1);
		cprint("open BGame Box ................... 打开装逼模式",5-1,1);
		cprint("Exit From BSchedule .............. 退出BWallet?",6-1,1);

		printx(ctrl);
		getcontrol();
		if ((13 == ch[0] && ctrl == 1-1) || '1' == ch[0] ){	
			return 's';
		}
		if ((13 == ch[0] && ctrl == 2-1) || '2' == ch[0] ){
			return 'a';
		}
		if ((13 == ch[0] && ctrl == 3-1) || '3' == ch[0] ){
			return 'm';	
		}
		if ((13 == ch[0] && ctrl == 4-1) || '4' == ch[0] ){
			return 'w';
		}
		if ((13 == ch[0] && ctrl == 5-1) || '5' == ch[0] ){
			return 'b';
		}
		if ((13 == ch[0] && ctrl == 6-1) || '6' == ch[0] ){
			return 'q';
		}
		gotoxy(0,0);
	}
}
*/
/* 欢迎界面里 打印光标 ‘* ’*/
/*
void printx(int yy){
	gotoxy(inix,yy+iniy);
	printf("*");
}
*/
/*
void cprint(const char *sen,int hang,int xh){
	int i = 0;
	gotoxy(inix,iniy+hang);
	if (xh == 1)
		printf("    %d,",hang+1);

	while ( *(sen+i) != '\0'){
		printf("%c",*(sen+i));
		i++;
	}
	return;
}
*/

//void getcontrol(){
//	ch[0] = getch();
//	if (ch[0] == -32){
//		ch[1] = getch();
//		if (ch[1] == 72){			/* ↑ */
//			if (ctrl-- <= 0 )
//				ctrl = 0 ;
//		}
//		else if (ch[1] == 80){		/* ↓ */
//			if (ctrl++ >= 5 )
//				ctrl = 5;
//		}
//	}
//	else if ('s' == ch[0] || 'S' == ch[0]){
//		if (ctrl++ >= 5 )
//		ctrl = 5;
//	}
//	else if ('w' == ch[0] || 'W' == ch[0]){
//		if (ctrl-- <= 0 )
//			ctrl = 0 ;
//	}
//	gotoxy(inix,ctrl+iniy);
//	printf(" ");	
//}

/*
int memu_for_BBOX(const char* user_name,char * command){
	int i;
	system("cls");
	while (1) {
		printf("     hello~~  %s,",user_name);
		printf(" Welcome to BBox press s&w to move '*'\n");
		printf("    ");
		cprint("CPython ....................... Extra",1-1,1);
		cprint("xfscnm? ................. Interesting",2-1,1);
		cprint("CTetrisRS ....................... Bug",3-1,1);
		cprint("BScript .................... Language",4-1,1);
		cprint("Exit ........................... Quit",5-1,1);
		printx(ctrl);
		getcontrol();
		if ((13 == ch[0] && ctrl == 1-1) || '1' == ch[0] || 'p' == ch[0]){
			i = 0;
			gotoxy(3,2+1-1);
			while (*(shaonv+i) != '\0'){
        		printf("%c",*(shaonv+i));
        		_sleep(extra_speed-25);
        		i++;
		    }
		    system("cls");
		    _sleep(400);
			system("CPythonUPPERi.exe");
		}
		
		if ((13 == ch[0] && ctrl == 2-1) || '2' == ch[0] || 'm' == ch[0]){
			i = 0;
			gotoxy(3,3+1-1);
			while (*(shaonv+i) != '\0'){
        		printf("%c",*(shaonv+i));
        		_sleep(extra_speed-25);
        		i++;
		    }
		    system("cls");
		    _sleep(400);
			system("mmmf.exe");
		}
		
		if ((13 == ch[0] && ctrl == 3-1) || '3' == ch[0] || 't' == ch[0]){
			i = 0;
			gotoxy(3,4+1-1);
			while (*(shaonv+i) != '\0'){
        		printf("%c",*(shaonv+i));
        		_sleep(extra_speed-25);
        		i++;
		    }
		    system("cls");
		    _sleep(400);
			system("CTetrisRS.exe");
		}	
		
		if ((13 == ch[0] && ctrl == 4-1) || '4' == ch[0] || 't' == ch[0]){
			i = 0;
			gotoxy(3,5+1-1);
			while (*(shaonv+i) != '\0'){
        		printf("%c",*(shaonv+i));
        		_sleep(extra_speed-25);
        		i++;
		    }
		    system("cls");
		    _sleep(400);
			system("BScript.exe");
		}
		
		if ((13 == ch[0] && ctrl == 5-1) || '5' == ch[0] || 'q' == ch[0]){
			gotoxy(3,2+5-1);
			system("cls");
			return;
		}
			system("cls");
	}
}
*/

