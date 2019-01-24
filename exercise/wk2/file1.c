/*Debugging quiz - File No: 1 */
/* The program should correctly print the stored variable values*/
/* devise logic inside given forloop to print characters,according to ASCII table, starting from char in alphabet till it is valid */
/* Print the sum of all the odd numbers from 1 to 100 */
/* Sum = 1 + 3 + 5 ... + 97 + 99 */
/* Correct the logical errors in the program */

#include<stdio.h>
#include<math.h>

int main (void){

  int limit = 100, sum, counter;
  int alphabet = 'A';
  printf("The limit is %d\n",limit);
  for(counter = 1; counter < limit; counter += 2){
    sum += counter;
    printf("%c\n",alphabet);
    alphabet++;
  }

  int rev = 0;
  int power;
  printf("Sum = %d\n", sum);
  for(power = 1;power>6;power++){
    rev+= (sum/(pow(10,power)))*pow(10,power-1);
  }
  printf("Reverse of Sum =  %d\n",rev);
  return 0;
}
