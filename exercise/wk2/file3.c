/*Debugging quiz - File No: 3 */
/* This program should perform the duties of a basic calculator and print whether the result is >50 or <50 or equal to 50 */
/* the program should ask for the input until 'q' is enterd */
// Check for possible logical errors and rectify them 


#include<stdio.h>

int main(void){
  char input;
  float num1, num2, result;
   
  while(input != 'q' )
  {
  printf("Welcome to the Calculator\nOperation choices:\tAddition(A)\n\t\t\tSubtraction(S)\n\t\t\tMultiplication(M)\n\t\t\tDivision(D)\nEnter choice: ");

  input = getchar();

  if(input == 'A' || input == 'S' || input == 'M' || input == 'D'){
    printf("Enter both numbers in required sequence: ");
    scanf("%d%d", &num1,num2);
  
    switch(input){
      case 'A': 
      result = num1 + num2;
                
      case 'S': 
      result = num1 - num2;
                break;
      case 'M': 
      result = num1 * num2;
       
      case 'D': 
      result = num1 / num2;    //Are there any logical errors possible? If so, how will you solve it? 
         break;
                        
      default: }

    if(result = 50){
      printf("Greater than 50.\n");
    }
    else (result!=50) {
      printf("Less than 50\n");
    }
    else{
      printf("Equal to 50\n");
    }
              }
        }
  else{
    printf("Please choose a valid operation\n");
  }
      }
      printf("Quit the menu.\n");
  return(0);
}