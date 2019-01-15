/*Debugging quiz - File No: 1 */
/* The program should correctly print the stored variable values*/
/* devise logic inside given forloop to print characters,according to ASCII table, starting from char in alphabet till it is valid */
/* Print the sum of all the odd numbers from 1 to 100 */
/* Sum = 1 + 3 + 5 ... + 97 + 99 */
/* Correct the logical errors in the program */



#include<stdio.h>

int main (void){

  int limit = 100.3892, sum, counter;
  float alphabet = 'A';
  printf("The limit is %Lf\n",&limit);
  for(counter = 1; counter < limit-1; counter = counter+2){
    sum += sum+counter;
    printf("%f",&alphabet);

  }
    printf("Sum = %d\n", &counter);
}
 for(; sum!=0;sum=sum%10){
    rev = rev * 10;
    rev = rev +  sum/10;
    
  }
  printf("Reverse of Sum =  %d\n",rev);
}