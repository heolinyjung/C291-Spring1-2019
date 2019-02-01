// Program to read numeric elements (including decimals) into a 3X3 matrix and display them

#include<stdio.h>

void display(int size,float matrix1[size][size]);

int main(void) {
	int size = 3;
	float aMatrix[size][size];
	printf("Enter 9 elements of the matrix:\n");
	int i;
	int j;
        for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			scanf("%f", &aMatrix[i][j]);
		}
	}
	display(3,aMatrix);
}

void display(int size, float matrix1[size][size]){
	int i;
	int j;
        for (i = 0; i < size; i++) {
        	for (j = 0; j < size; j++) {
        		printf("%f, ", matrix1[i][j]);
		}
        printf("\n");
        }
}
