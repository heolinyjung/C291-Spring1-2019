// The factorial of an integer is the product of the number with all
// the positive integers below it.

// For example: Factorial of 5 = 5 * 4 * 3 * 2 * 1 = 120

#include<stdio.h>

int factorial(int);

int main(void) {
	int n;
	printf("Debugging Practice 1 - Quiz 3, Q3\n\n");
        printf("Please enter the number whose factorial you wish to find:");
        scanf("%d", &n);
        int fact = factorial(n);
        printf("The factorial of %d is %d\n", n, fact);
	return 0;
}

int factorial(int number) {
	int fact = 1;
	int i;
	for (i = 1; i <= number; i++){
		fact = fact*i;
	}
	return fact;
}
