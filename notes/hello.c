/* Heoliny Jung */
// This is my first C program

#include<stdio.h>
int main(void)
{
 char myChar;
 printf("Please enter a character: ");
 scanf("%c",&myChar);
 printf("Value: %c stored at address %p \n",myChar, &myChar);
 return 0;
}
