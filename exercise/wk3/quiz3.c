/* Instructions:
 *
 *
 1. Write a program to assign Grade to Student. 
	Get the number of subjects from user. 
	Calculate percentage and return the grade associated with a range of marks.

 2. The range of marks and the associated grades are as follows:
     a. [97-100] = A+
     b. [90-97) = A
     c. [80-90) = B
     d. [70-80) = C
     e. less than 70 is a failing grade and should be given an F
     e. greater than 100 or less than 0 is invalid and your code should print "Invalid"

 3. Use the skeleton code provided below to create a new function "printGrade" with its appropriate
    data type for input of marks. For example, printGrade(<data type> marks). You should allow decimal values.

 4. Use print statements in your function to display the grade. For example, if the input marks is 77, the output should read:
        "Your grade is : C"

 5. Please adhere to standard C syntax conventions and use comments to explain your code. Failure to do so will result in a penalty.

 *
 *
 * */

#include<stdio.h>
void printGrade(float marks ){
// Hint: use if and else if conditions to print the grade 
}
int main(void){
	char ch;
	float marks;
	int subject;
	do {
		printf("How many subjects do you have ?");
		
		// get the number of subjects from user 
		
		printf("Enter marks of all subjects : " );
		
		// get the marks of all subjects and store them in an array (Hint: You can use for loop to get marks of subjects)
		
		// do average of all marks and store it in different variable called avg
		// avg contains average of all marks of subjects
		
		printGrade(avg);
		printf("/nDo you want to continue? (Y/N) ");
		scanf(" %c",&ch);
	} while(ch == 'y'|| ch == 'Y');
	return 0;
}





/* OUTPUT:
How many subjects do you have ? 4
Enter marks of all subjects :
77
88
99
89
Your grade is : B
/nDo you want to continue? (Y/N)
*/