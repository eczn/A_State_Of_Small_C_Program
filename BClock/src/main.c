#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define PI  3.141592
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void get_time(char now_time[]){
	long int week_time = 0,i=0,time_num = 0;
	time_t nowtime;
	time(&nowtime);
	struct tm *timeinfo = localtime( &nowtime );
	time(&nowtime);
	timeinfo = localtime( &nowtime );
	
	now_time[0] = timeinfo->tm_hour;
	now_time[1] = timeinfo->tm_min; 
	now_time[2] = timeinfo->tm_sec;
}

void calc_position(double result[3][2],char now_time[],float offset){
	int i;
	int len[3] = {240,240,280};
	int para[3] = {6,30,30};
	double t[3] = {0.0,0.0,0.0}; 
	double temp;
	
	t[2] = now_time[2] + offset; 
	t[1] = now_time[1] + t[2]/60; 
	t[0] = now_time[0] + t[1]/60; 
	for (i=0;i<3;i++){

		result[i][0] = 300 + len[i] * sin(PI*( t[i] )/para[i]);
		result[i][1] = 300 - len[i] * cos(PI*( t[i] )/para[i]);
	}
	
}

int main(int argc, char *argv[]) {
    HWND    hwnd;
    HDC    hdc;
	hwnd = GetConsoleWindow();
    hdc = GetDC(hwnd);
	int t = 0;
	double x0,y0; 
	char sec_store;
	char time_table[3]; // 第一个是hour 第二个是min 第三个是sec 
	double position[3][2];	// 第一行是hour 第二行是min 第三个行sec 
	float offset = 0;
	int sec_count = 0 ;
	
	system("color FD");
	while (1){
		get_time(time_table);
		if (time_table[2]!=t){
			t=time_table[2];
			sec_count++;
		}
		
		offset = ((float)clock() - sec_count*1000)/1000;
		
		calc_position(position,time_table,offset);
//		printf("%d\n%f\n%d",time_table[2],offset,sec_count);
	
		
		MoveToEx(hdc,297,297,NULL);
		LineTo(hdc,(int)position[0][0],(int)position[0][1]);
		LineTo(hdc,303,303);
		
		MoveToEx(hdc,297,297,NULL);
		LineTo(hdc,(int)position[1][0],(int)position[1][1]);
		LineTo(hdc,303,303);

		MoveToEx(hdc,297,297,NULL);
		LineTo(hdc,(int)position[2][0],(int)position[2][1]);
		LineTo(hdc,303,303);
		
		
		_sleep(100);
		system("cls");
		
	}
	
	
	return 0;
}
