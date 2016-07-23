#include <stdio.h>

struct DATE {
	int year;
	int date;
	int ie_date;
	int res_2;					/*			*/
	int res_3;					/*	保留位	*/
	int res_4; 					/*			*/
	char note[8][196];
	struct DATE *up;
	struct DATE *down;
};

void load(struct DATE *head){
	int eff_num = 0;
	int buffer; 
	struct DATE *temA = NULL;
	struct DATE *temB = NULL; 
	FILE *fp = NULL;
	fp = fopen("ScheduleData","r+");
	
	temA = (struct DATE *)malloc(sizeof(struct DATE));
	temA->down = NULL;
	temA->up = head; 
	head->down = temA;
	while (feof(fp) == 0){
		eff_num = fread(temA,1,1592,fp);
		if (eff_num != 0){
			temB = (struct DATE *)malloc(sizeof(struct DATE));
			temA->down = temB; 
			temB->up = temA;
			temB->down = NULL;
			temA = temB; 
		}
		Sleep(100);
//		printf("%d  ",eff_num);
//		system("pause");
	}
	fclose(fp);
	return; 
}

void save(struct DATE *head){
	int eff_num=0,i,k;
	int buffer;
	struct DATE *temA = NULL;
	FILE *fp = NULL;
	fp = fopen("ScheduleData","w+");
	

	temA = head->down;
	temA->note[7][195] = '\0';
//	temA->note[0][0] = 'd'; 
	while ( temA->down != NULL ){
		eff_num += 4*fwrite(temA,4,6,fp);				/* 保存六个整形 */
//		printf("wri22: %d \n",eff_num);
		for (k=0;k<8;k++){
			for (i=0;i<196;i++){
				eff_num += fwrite(temA->note[k]+i,1,1,fp);
			}
		}
		temA = temA->down;
	}
//	printf("wri: %d \n",eff_num);
	fclose(fp);
	return;
}

