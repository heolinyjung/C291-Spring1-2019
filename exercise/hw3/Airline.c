/*
 * Heoliny Jung
 * C291
 * Prof Bhutta
 * Assignment 3 : Airline
 * 1/29/2019
 */

#include<stdio.h>

//Static variables
static int seats[10][4] = {}; //10 rows, 4 columns (1-10, A-D)
static char* names[10][4] = {}; //name pointer array for names of each passenger
int current[2] = {}; //Current seat in seats array
char* name = NULL; //user name

//Function definitions
void planeStatus(void); //prints plane diagram and all names
void userStatus(void); //prints users current name and seat
int* findSeat(int); //finds a seat in a certain class determined by int
void printPass(); //prints boarding pass
char rowConvert(int); //converts numbers 0-3 to A-D

int main(void){
	
	printf("---------------\nWelcome to C291 Airlines Digital Booking System\n");
	int choice = 0;
	while(choice!=5){

		printf("---------------\nPlease select an option from the menu: (input 1,2,3,4)\n");
		printf("1. See status\n2. Book a seat\n3. Upgrade/downgrade seat\n4. Print Boarding Pass\n5. Exit\n");
		scanf(" %d",&choice);
		int class = 0;
		int* seat;
		int updown;
		switch(choice){
			case 1: planeStatus();userStatus();
				break;
			case 2: class = 0;
				printf("What class seat would you like to book?\n1. First class\n2. Business class\n3. Economy class\n");
				scanf(" %d",&class);
				seat = findSeat(class);
				if(seat[1]!=4){
					printf("Here is the seat we found:\n");
					printf("%d%c\n",seat[0]+1,rowConvert(seat[1]));
					current[0] = seat[0];
					current[1] = seat[1];
					seats[seat[0]][seat[1]] = 1;
					names[seat[0]][seat[1]] = name;
					printf("Here is your boarding information: \n");
					userStatus();
				}
				else{
					printf("No available seats in selected class.\n");
				}
				break;
			case 3: updown = -1;
				if(current[0]<2){
					seat = findSeat(2);
				}
				else if(current[0]<4){
					char c;
					printf("Would you like to upgrade to first class or downgrade to economy?(u/d):\n");
					scanf(" %c",&c);
					if(c=='u'){
						seat = findSeat(1);
					}
					else if(c=='d'){
						seat = findSeat(3);
					}
				}
				else if(current[0]<10){
					seat = findSeat(2);
				}
				else{
					printf("No current reservation found.\n");
				}
				if(seat[1]!=4){
					printf("Here is your new boarding information:\n");
					current[0] = seat[0];
					current[1] = seat[1];
					seats[seat[0]][seat[1]] = 1;
                                        names[seat[0]][seat[1]] = name;
					printf("%d%c",current[0],rowConvert(current[1]));
				}
				break;
			case 4: printPass();
				break;
			default: printf("Not a valid selection.\n");
		}
	}
	printf("Thank you for flying C291 Airlines!\n");
	return 0;
}

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

void userStatus(void){
	printf("%s\t\t%d%c\n",names[current[0]][current[1]],current[0]+1,rowConvert(current[1]));
}

int* findSeat(int class){
        int seat[2] = {};
        printf("Please input your name: \n");
        scanf("%s",name);
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
		while(!found&&i<end){
			int j = 0;
			while(!found&&j<4){
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
