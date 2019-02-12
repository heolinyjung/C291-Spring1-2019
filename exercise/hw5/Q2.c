
/*
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * 2/12/2019
 * Assignment 5: Q2 - Health Profile
 */

#include<stdio.h>
#include<string.h>
#include<time.h>

//constant arrays
char* MONTHS[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char* GENDERS[] = {"Female","Male","Other"};

//Function prototypes
char* getMonthString(void);
char* getGenderString(void);
unsigned int calcAge(void);
double calcBMI(void);
double calcMaxHeartRate(void);
double calcHeartRateRange(void);

//static profile struct w typedef
typedef struct HealthProfiles{
	char firstName[20];
	char lastName[20];
	char gender; //f = female, m = male, o = other
	struct {
		short int day;
		short int month;
		int year;
	} DOB;
	int height;
	int weight;
	struct {
		//for all below: 0 = none, 1 = yes
		int heartProblem;
		int bloodPressure;
		int cancer;
	}FamHistory;
}HProfile;
static HProfile profile;

int main(void){

	
	printf("--------------------------------------\n");
	printf("Welcome to your digital health profile\n");
	printf("--------------------------------------\n\n");
	printf("What is your first name?\n");
	scanf("%s",profile.firstName);
	printf("What is your last name?\n");
	scanf(" %s",profile.lastName);
	printf("What is your gender?\nMale (m)\nFemale (f)\nOther (o)\n");
	scanf(" %c",&profile.gender);
	printf("What is your birthday? (DAY MONTH YEAR)\n");
	scanf("%hd %hd %d",&(profile.DOB.day),&(profile.DOB.month),&(profile.DOB.year));
	printf("What is your height?\n");
        scanf("%d",&profile.height);
	printf("What is your weight?\n");
        scanf("%d",&profile.weight);
	printf("Has anyone in you family ever had heart problems? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.heartProblem);
	printf("Does your family have a history of high blood pressure? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.bloodPressure);
	printf("Has anyone in you family ever had cancer? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.cancer);
	printf("--------------------------------------\n");
	printf("DOB month: %s\n",*getMonthString);
	printf("Gender: %s\n",*getGenderString);
	printf("Age: %d\n",calcAge);
	return 0;
}

char* getMonthString(){
	return MONTHS[profile.DOB.month];
}

char* getGenderString(){
	char* gPtr;
	switch(profile.gender){
		case 'f': gPtr = (GENDERS[0]);
			break;
		case 'm': gPtr = (GENDERS[1]);
			break;
		case 'o': gPtr = (GENDERS[2]);
		default:;
	}
	return gPtr;
}

unsigned int calcAge(){
	struct tm timeStruct = *localtime(&(time_t){time(NULL)});
	int year = (int)(atoi(timeStruct.tm_year)) + 1900;
	return year - profile.DOB.year;
}
