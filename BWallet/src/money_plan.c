#include <stdio.h>

void money_plan_get_and_save(){
	int i = 0;
	char article[1024] = { '\0' };
	
	system("cls");
	printf("_________________文本数据__________________\n");
	for (i=0;i<1024;i++){
		article[i] = getch();
		printf("%c",article[i]);
		if (article[i] == 8) {
			printf(" ");
			putchar(8);
			i-=2;
		}
		if (article[i] == -32){
			i -= 2;
		}
		if (article[i] == 13){
			break;
		}
	}
	system("cls");
	if (article[0] == 13) return;
	
	FILE *fp_for_mp = NULL;
	fp_for_mp = fopen("MoneyPlan","w+");
	i = fwrite(article,1,1024,fp_for_mp);
	fclose(fp_for_mp);
	if (i == 0){
		printf("\n\n write error!!!");
		system("pause");
	}
}

void money_plan_load_and_print(){
	char article[1024] = { '\0' };
	int flag = 0;
	FILE *fp_for_mp = NULL; 
	
	flag = fp_for_mp = fopen("MoneyPlan","r+");
	if (flag == 0) return;
	
	flag ^= flag;
	flag = fread(article,1,1024,fp_for_mp);
	if (flag == 0) return;
	printf("%s\n",article);
	fclose(fp_for_mp);
}

