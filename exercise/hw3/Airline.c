/*
 * Heoliny Jung
 * C291
 * Prof Bhutta
 * Assignment 3 : Airline
 * 1/29/2019
 * Resubmitted 2/19/2019
 */

#include<stdio.h>
#include<string.h>

//Static variables
static int seats[10][4] = {}; //10 rows, 4 columns (1-10, A-D)
static char* names[10][4] = {}; //name pointer array for names of each passenger
static int current[2] = {0,4}; //Current seat in seats array. When current[1] == 4, no seat has been claimed
static char name[30]; //user name
//static char * namePtr = name; //name pointer

//Function definitions
void planeStatus(void); //prints plane diagram and all names
void userStatus(void); //prints users current name and seat
int* findSeat(int); //finds a seat in a certain class determined by int
void printPass(); //prints boarding pass
char rowConvert(int); //converts numbers 0-3 to A-D

int main(void){
	
	printf("---------------\nWelcome to C291 Airlines Digital Booking System\n");
	char choice = '0';
	int class;
	printf("---------------\n");
	printf("Please input your name: \n");
        scanf(" %s",name);
	while(choice!='5'){
		sleep(1);		
		choice = '0';
		printf("---------------\n");
		printf("Please select an option from the menu: (input 1,2,3,4,5)\n");
		printf("1. See status\n2. Book a seat\n3. Upgrade/downgrade seat\n4. Print Boarding Pass\n5. Exit\n");
		scanf(" %c",&choice);
		int* newSeat;
		int updown;
		fflush(stdout);
		switch(choice){
				//get status
			case '1': planeStatus();userStatus();
				break;

				//find a seat
			case '2': if(current[1]==4){
					class = 0;
					printf("What class seat would you like to book?\n1. First class\n2. Business class\n3. Economy class\n");
					scanf(" %d",&class);
					newSeat = findSeat(class);
					if(newSeat[1]!=4){
						printf("Here is the seat we found: ");
						printf("%d",newSeat[0]+1);
						printf("%c\n",rowConvert(newSeat[1]));

						current[0] = newSeat[0];
						current[1] = newSeat[1];
						seats[current[0]][current[1]] = 1;

						names[current[0]][current[1]] = name;

						printf("Here is your boarding information: \n");
						userStatus();
					}
					else{
						printf("No available seats in selected class.\n");
					}
				}
				else{
					printf("You have already booked a flight. Here are the details:\n");
					userStatus();
				}
				break;

				//Upgrade/downgrade
			case '3': updown = -1;
				if(current[1]==4){
					printf("No current reservation found.\n");
				}
				else if(current[0]<2){
					newSeat = findSeat(2);
				}
				else if(current[0]<4){
					char c;
					printf("Would you like to upgrade to first class or downgrade to economy?(u/d):\n");
					scanf(" %c",&c);
					if(c=='u'){
						newSeat = findSeat(1);
					}
					else if(c=='d'){
						newSeat = findSeat(3);
					}
				}
				else{
					newSeat = findSeat(2);
				}
				if(newSeat[1]!=4){
					seats[current[0]][current[1]] = 0; //remove old reservation
					current[0] = newSeat[0];
                                        current[1] = newSeat[1];
                                        seats[current[0]][current[1]] = 1; //add new reservation

                                        names[current[0]][current[1]] = name;
                                        printf("Here is your new boarding information: \n");
                                        userStatus();
				}
				break;

				//Print boarding pass
			case '4': sleep(1);printPass();
				break;
			case '5': break;

			default: printf("Not a valid selection.\n");choice = '0';break;
		}
	}
	printf("Thank you for flying C291 Airlines!\n");
	return 0;
}

/*
 * Converts an int the represents a row to a char A, B, C, or D
 */
char rowConvert(int row){
	char c;
	switch(row){
		case 0 : c = 'A';
			break;
		case 1 : c = 'B';
			break;
		case 2 : c = 'C';
			break;
		case 3 : c = 'D';
			break;
		default:;
	}
	return c;
}

/*
 * Prints the plane grid
 */

void planeStatus(void){
	printf("---------------\nCurrent seat availability:\n AB CD\n");
	int i;
	for(i = 0;i<10;i++){
		printf("|");
		int j;
		for(j = 0;j<4;j++){
			if(j==2){
				printf(" ");
			}
			printf("%d",seats[i][j]);
		}
		printf("| %d\n",i+1);
	}
        for(i = 0;i<10;i++){
		int j;
                for(j = 0;j<4;j++){
                        if(seats[i][j]==1){
                                printf("%s\t\t%d%c\n",names[i][j],i+1,rowConvert(i));
                        }
                }
        }
}

/*
 * Prints the name of cutomer and their seat
 */

void userStatus(void){
	printf("%s\t\t%d%c\n",names[current[0]][current[1]],current[0]+1,rowConvert(current[1]));
}

int* findSeat(int class){
        int seat[2] = {0,0};
        int start;
        int end;
        int cont = 1;
        switch(class){
                case 1: start = 0;
                        end = 2;
                        break;
                case 2: start = 2;
                        end = 4;
                        break;
                case 3: start = 4;
                        end = 10;
                        break;
                default: cont = 0;
        }
	int found = 0;
        if(cont){
		int i = start;
		while((!found)&&i<end){
			int j = 0;
			while((!found)&&j<4){
                                if(seats[i][j]==0){
                                        seats[i][j] = 1;
					found = 1;
					seat[0] = i;
					seat[1] = j;
				}
				j++;
			}
			i++;
		}
        }
        else{
                seat[1] = 4;
        }
	int* seatptr = seat;
        return seatptr;
}

void printPass(void){
	printf("-----------\nPassenger: %s\nSeat: %d%c\n----------\n",names[current[0]][current[1]],current[0],rowConvert(current[1]));
}
