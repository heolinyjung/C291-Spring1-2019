/* 
 * Heoliny Jung
 * C291
 * Prof. Bhutta
 * Assignment2: Nim Game
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

//class variables
int compBrain;

//Function declarations
int randLim(int);
int compTurn(int);
int playerTurn(int);

int main(void){

 srand(time(0)); //sets pseduorandom seed for optimal randomization

 int pileSize = randLim(90)+10; //90 = limit, + 10 for 10-100
 int whosTurn = 0; //randLim(1); 0 = comp, 1 = player
 compBrain = 0;//randLim(1); 0-1, 0 = stupid, 1 = smart

 if(whosTurn){
  printf("You go first!\n");
 }
 else{
  printf("Computer goes first!\n");
 }

 if(compBrain){
  printf("The computer is smart! Good luck.\n");
 }
 else{
  printf("The computer is stupid!\n");
 }

 printf("The pile size is %d\n",pileSize);

 while(pileSize>1){
  int amt = 0;
  if(whosTurn==0){
   amt = compTurn(pileSize);
   printf("The computer removed %d from the pile.\n",amt);
   whosTurn = 1;
  }
  else{
   amt = playerTurn(pileSize);
   printf("You removed %d form the pile.\n",amt);
   whosTurn = 0;
  }
  pileSize-=amt;
  printf("The remaining amount in the pile is %d\n",pileSize);
 }
 if(whosTurn == 1){
  printf("Computer wins!\n"); 
 }
 else{
  printf("You win!\n");
 }

 return 0;
}

/* 
 * Returns a random number between 0 and limit inclusive
 * Example found online as how to distribute rand ints more evenly than rand()%range
 */
int randLim(int limit){

 int divisor = RAND_MAX/(limit+1);
 int retval;

 do{
  retval = rand() / divisor;
 } while (retval > limit);

 return retval;
}

/* 
 * Player's turn function
 * Scans input from user and returns that int if within bounds of 0<int<pileSize/2
 */
int playerTurn(int pileSize){
 int input = 0;
 
 while(1){
  printf("Enter amount to remove: ");
  scanf("%d",&input);
  if(input<1||input>pileSize/2){
   printf("Not a valid amount.\n");
  }
  else{
   return input;
  }
 }
}

/*
 * Computer's turn function
 * Using rules 0 = stupid, 1 = smart, will return amount taken for the computer's turn.
 */
int compTurn(int pileSize){
 int amt = 0;
 if(compBrain == 1){
  double n = 0;
  while(amt<pileSize/2){
   amt = pow(2.0,n++)-1;
  }
 }
 else{
  int lim = (pileSize/2);
  amt = randLim((lim)-1)+1;
 }
 return amt;
}
