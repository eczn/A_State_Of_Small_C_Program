#include <stdio.h>
/* �ַ�ѭ����λ������� */
/*   ch from 65 ~ 90    */

char encode(char ch){						/* ���� */	
	if ( 65<=ch && ch<=90 ){				/* ��д */
		ch -= 65;
		ch +=  3;
		if (ch >= 26 )
			ch -= 26; 		
	} else if ( 97<=ch && ch<=122 ){			/* Сд */
		ch -= 97;
		ch +=  3;
		if (ch >= 26 )
			ch -= 26; 
	}
	return ch;
}

char decode(char ch){						/* ���� */
	if ( 65<=ch && ch<=90 ){				/* ��д */
		ch -= 65;
		ch -=  3;
		if (ch < 0 )
			ch += 26; 		
	} else if ( 97<=ch && ch<=122 ){			/* Сд */
		ch -= 97;
		ch -=  3;
		if (ch <  0 )
			ch += 26; 
	}	
	return ch; 
}


