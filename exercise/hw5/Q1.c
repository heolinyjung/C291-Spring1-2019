/*
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * 2/12/2019
 * Assignment 5: Q1
 */

#include<stdio.h>
#include<string.h>

int main(void){

	struct customer {
		char lastName[ 20];
		char firstName[ 20]; 
		unsigned int customerNumber;
		struct { 
			char phoneNumber[ 11 ]; 
			char address[ 60 ]; 
			char city[ 20]; 
			char state[ 3 ]; 
			char zipCode[ 6 ]; 
		} personal;
	} customerRecord, *customerPtr;
	customerPtr = &customerRecord;

	// Some tests
	//char pNum[] = "6316551242";
	//strcpy(customerRecord.personal.phoneNumber,pNum);

	//a)
	printf("%19s\n",customerRecord.lastName);
        //b)
	printf("%19s\n",customerPtr->lastName);
        //c)
	printf("%19s\n",customerRecord.firstName);
        //d)
	printf("%19s\n",customerPtr->firstName);
        //e)
	printf("%u\n",customerRecord.customerNumber);
        //f)
	printf("%u\n",customerPtr->customerNumber);
        //g)
	printf("%10s\n",customerRecord.personal.phoneNumber);
        //h)
	printf("%10s\n",customerPtr->personal.phoneNumber);
        //i)
	printf("%p\n",&(customerRecord.personal));
        //j)
	printf("%p\n",&(customerPtr->personal));
        //k)
	printf("%19s\n",customerRecord.personal.city);
        //l)
	printf("%19s\n",customerPtr->personal.city);
        //m)
	printf("%2s\n",customerRecord.peronal.state);
        //n)
	printf("%2s\n",customerPtr->personal.state);
        //o)
	printf("%5s\n",customerRecord.personal.zipCode);
        //p)
	printf("%5s\n",customerPtr->personal.zipCode);

	return 0;
}
