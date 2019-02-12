/*
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * 2/12/2019
 * Assignment 5: Pack chars
 */

#include<stdio.h>

//prototypes
unsigned int packCharacters(char, char, char, char);
void printBinary(unsigned);

int main(void){
	char one;
	char two;
	char three;
	char four;
	printf("Please input a character: ");
	scanf("%c",&one);
	printf("Please input another character: ");
        scanf(" %c",&two);
	printf("Please input another character: ");
        scanf(" %c",&three);
	printf("Please input another character: ");
        scanf(" %c",&four);
	unsigned int packed = packCharacters(one,two,three,four);
	printf("Char one:\n");
	printBinary(one);
	printf("Char two:\n");
	printBinary(two);
	printf("Char three:\n");
	printBinary(three);
	printf("Char four:\n");
	printBinary(four);
	printf("Packed unsigned int:\n");
	printBinary(packed);
	return 0;
}

unsigned int packCharacters(char c1, char c2, char c3, char c4){
	unsigned int ans = c1;
	ans = ans<<(8);
	ans |= c2;
	ans = ans<<(8);
	ans |= c3;
	ans = ans<<(8);
	ans |= c4;
	return ans;
}

void printBinary(unsigned n){
	unsigned i;
	for(i = 1 << 31; i > 0; i = i/2){
		(n & i)? printf("1"):printf("0");
	}
	printf("\n");
}
