/*
 * Quiz 7
 * Heoliny Jung
 */

#include<stdio.h>

int main(void){

 int hex;
 unsigned int r = 200;
 printf("%12u\n",r);
 //scanf("%x",&hex);
 printf("%d\n",800);
 printf("%+d\n",800);
 printf("%#x\n",200);
 //char m[10];
 //scanf("%[^z]9s",m);
 //printf("%s\n",m);
 printf("%09.3f\n",3.150);
 //char s[15];
 //scanf("\"%[^\"]s",s);
 //printf("%s\n",s);
 printf("%c\n", "This is a string");
 printf( "O\n%#o\n%#X\n%e\n", 17, 17, 1008.83619 );
 printf( "% ld\n%+ld\n", 7000000, 4000000 );
 printf( "%10.3E\n", 454.93738 );
 printf( "%10.3g\n", 464.93738 );
 printf( "%10.3f\n", 454.93738 );
 printf("%d\n",10.937);
 return 0;
}
