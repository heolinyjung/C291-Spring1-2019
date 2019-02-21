#include<stdio.h>

int main(void){
	int a = 0;
	printf("%x\n",~a); //compliment operation
	int b = 20 & 32; //logical AND bitwise operation
	printf("%d\n",b);
	int c = 20 | 32; //logical OR bitwise operation
	printf("%d\n",c);
	printf("%d\n",2<<2); //left shift every bit by two (0010(==2) -> 1000(==8))
	return 0;
}
