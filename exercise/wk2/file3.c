/*Debugging quiz - File No: 3 */
/* This program should perform the duties of a basic calculator and print whether the result is >50 or <50 or equal to 50 */
/* the program should ask for the input until 'q' is enterd */
// Check for possible logical errors and rectify them 


#include<stdio.h>

int main(void){
  char input;
  float num1, num2, result;
  int divZeroErr;

  printf("-------------------------\n");
  printf("Welcome to the Calculator\n");
   
  while(input != 'q'){
    printf("-------------------------\n");
    printf("Operation choices:\tAddition(A)\n\t\t\tSubtraction(S)\n\t\t\tMultiplication(M)\n\t\t\tDivision(D)\n\t\t\tQuit the menu(q)\nEnter choice: ");

    //Space for handling extra whitespace
    scanf(" %c",&input);

    if(input == 'A' || input == 'S' || input == 'M' || input == 'D'){
      printf("Enter both numbers in required sequence: ");
      scanf("%f%f", &num1,&num2);
      divZeroErr = 0;
  
      switch(input){
        case 'A': 
        result = num1 + num2;
                break;
        case 'S': 
        result = num1 - num2;
                break;
        case 'M': 
        result = num1 * num2;
                break;
        case 'D':
        //Check for div by zero
        if(num2 == 0){
          printf("Error: cannot divide by zero\n");
          divZeroErr = 1;
        }
        else{
          result = num1 / num2;
        } 
                break;                        
        default:;
      }
      
      if(!divZeroErr){
        if(result > 50){
          printf("Greater than 50\n");
        }
        else if(result < 50) {
          printf("Less than 50\n");
        }
        else{
          printf("Equal to 50\n");
        }
      }
    }
    else{
      if(input!='q')
        printf("Please choose a valid operation\n");
    }
  }
  return(0);
}
