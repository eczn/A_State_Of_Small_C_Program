#include<stdio.h>

int calc(){
	int term,result,flag = 0,end = 0;
	char ch;
	ini_calc_area(); 
	gotoxy(0,28); 
	scanf("%d",&result);					/* scanf输入会留下一个回车		*/
	do {									/* 很多人视其为缺陷				*/
		ch=getchar();						/* 但是不是，因为这个回车的 	*/
	} while ( ch == ' ' ) ;					/* 作用应该相当于字符数组末尾 	*/
	scanf("%d",&term);						/* 的'\0' 用来标记结束(输入) 	*/

	while ( 1 ){          					/* 流的概念深入人心 */
		if ( ch == '+' ){
			result = result + term;
		}
		else if ( ch == '-' ) {           
			result = result - term;
		}
		else if ( ch == '/' ){
			result = result / term; 
		}
		else if ( ch == '*' || ch == 'x' ){
			result = result * term; 
		}
		do {								/* 循环读取运算符，直到不是空格 */
			ch = getchar();	
		} while ( ch == ' ' );
		if (ch == '\n'){					/* 如果读到 回车， 结束 */
			break;
		}
		flag = scanf("%d",&term);
    }
    gotoxy(0,27);
	printf("result: %d",result);
	return result;
}

void ini_calc_area(){						/* 算术区重置,用空格覆盖 */
	gotoxy(0,27);
	printf("                                        \n                                             ");
}

