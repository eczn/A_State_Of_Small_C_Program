#include <stdio.h>
#include <math.h>

void main(){
	float x,y; 
	float a = 1;
//	float z = x*x+y*y;
	for (y = 1.5f; y > -1.5f; y -= 0.1f){
		for ( x = -1.5f; x < 1.5f; x += 0.05f){
            a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
			/*
			if ( x*x + y*y + 1.1*x == 1.1*sqrt(z)  ) 
				printf("**");
			else printf("  ");
			*/
		}
		putchar('\n');
	}
}

