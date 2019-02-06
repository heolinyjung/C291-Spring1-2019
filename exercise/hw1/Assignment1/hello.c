/* Heoliny Jung */
// This is my first C program

#include<stdio.h>
int main(void)
{
 printf("\"{Hello/\\Welcome back to IU!}, This is Spring 2019's 1st 8 Week Course\"");
 int cont;
 cont = 1;
 while(cont==1){
  printf("\nHeoliny Jung");
  fflush(stdout);
  int count;
  count = 5;
  while(count>0){
   printf(".");
   count=count-1;
   sleep(2);
   fflush(stdout);
  }
 }
 return 0;
}
