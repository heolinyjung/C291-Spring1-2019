
/*
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * 2/12/2019
 * Assignment 5: Q2 - Health Profile
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//constant arrays
char* MONTHS[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char* GENDERS[] = {"Female","Male","Other"};

//Function prototypes
char* getMonthString(void);
char* getGenderString(void);
int calcAge(void);
void calcBMI(void);
double calcMaxHeartRate(void);
void calcTargetHeartRange(void);
void displayProfile(void);

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
	printf("What is your birthday? (DD MM YYYY)\n");
	scanf("%hd %hd %d",&(profile.DOB.day),&(profile.DOB.month),&(profile.DOB.year));
	printf("What is your height in inches?\n");
        scanf("%d",&profile.height);
	printf("What is your weight in pounds?\n");
        scanf("%d",&profile.weight);
	printf("Has anyone in you family ever had heart problems? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.heartProblem);
	printf("Does your family have a history of high blood pressure? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.bloodPressure);
	printf("Has anyone in you family ever had cancer? (0 = no, 1 = yes)\n");
        scanf("%d",&profile.FamHistory.cancer);
	printf("--------------------------------------\n");
	displayProfile();
	printf("Age: %d\n",calcAge());
	calcBMI();
	printf("Max heart rate: %.2f\n",calcMaxHeartRate());
	calcTargetHeartRange();
	return 0;
}

void displayProfile(){
	printf("Name: %s %s\n",profile.firstName,profile.lastName);
	printf("Gender: %s\n",getGenderString());
	printf("Date of birth: %s %hd %d\n",getMonthString(),profile.DOB.day,profile.DOB.year);
	printf("Height: %d\"\n",profile.height);
	printf("Weight: %d lbs\n",profile.weight);
	if(profile.FamHistory.heartProblem){
		printf("Possible inheritance of heart problems.\n");
	}
	else{
		printf("No family history of heart problems.\n");
	}
	if(profile.FamHistory.bloodPressure){
                printf("Possible inheritance of high blood pressure.\n");
        }
        else{
                printf("No family history of hight blood pressure.\n");
        }
	if(profile.FamHistory.cancer){
                printf("Possible likelyhood of cancer.\n");
        }
        else{
                printf("No family history of cancer.\n");
        }
}

char* getMonthString(){
	return MONTHS[profile.DOB.month-1];
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

int calcAge(){
	char year[5];
	int yearI;

	time_t itsTime = time(NULL);
	struct tm* bigChungus = localtime(&itsTime);
	strftime(year, 5, "%Y", bigChungus);

	yearI = atoi(year);
	return yearI - profile.DOB.year;
}

void calcBMI(){
	double bmi = (profile.weight * 703.0)/(profile.height*profile.height);
	printf("BMI: %.2f\n",bmi);
	if(bmi<18.5){
		printf("You are underweight.\n");
	}
	else if(bmi<24.9){
                printf("You are at a normal BMI.\n");
        }
	else if(bmi<29.9){
                printf("You are overweight.\n");
		if(profile.FamHistory.cancer){
			printf("With your BMI and family history of cancer, we advise you to see and oncologist.\n");
		}
        }
	else{
                printf("You are obese.\n");
		if(profile.FamHistory.cancer){
                        printf("With your BMI and family history of cancer, we advise you to see and oncologist.\n");
                }
        }
}

double calcMaxHeartRate(){
	return (double)220-calcAge();
}

void calcTargetHeartRange(){
	double max = calcMaxHeartRate();
	double lower = max*0.5;
	double upper = max*0.75;
	printf("Target heart range: %.2f - %.2f BPM\n",lower,upper);
	if(profile.FamHistory.heartProblem || profile.FamHistory.bloodPressure){
		printf("With your family history, if your heart rate is outside this range, we recommend you see your physician.\n");
	}
}
