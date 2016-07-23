#include <stdio.h>
/* 字符循环移位解码编码 */
/*   ch from 65 ~ 90    */

char encode(char ch){						/* 编码 */	
	if ( 65<=ch && ch<=90 ){				/* 大写 */
		ch -= 65;
		ch +=  3;
		if (ch >= 26 )
			ch -= 26; 		
	} else if ( 97<=ch && ch<=122 ){			/* 小写 */
		ch -= 97;
		ch +=  3;
		if (ch >= 26 )
			ch -= 26; 
	}
	return ch;
}

char decode(char ch){						/* 解码 */
	if ( 65<=ch && ch<=90 ){				/* 大写 */
		ch -= 65;
		ch -=  3;
		if (ch < 0 )
			ch += 26; 		
	} else if ( 97<=ch && ch<=122 ){			/* 小写 */
		ch -= 97;
		ch -=  3;
		if (ch <  0 )
			ch += 26; 
	}	
	return ch; 
}


