/* Heoliny Jung
 * C291
 * Prof. Bhutta
 * Assignment2: Nim Game
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Function declarations
in randLim(int limit);

int main(void){

 srand(time(0)); //sets pseduorandom seed for optimal randomization

 int pileSize = randLim(90)+10; //90 = limit, + 10 for 10-100
 int whoGoesFirst = randLim(1); //0-1
 int compBrain = randLim(1); //0-1

 while(pileSize>0){
  if(whoGoesFirst==0){
   whoGoesFirst = 1;
  }
  else{
   whoGoesFirst = 0;
  }
  
 }

 return 0;
}

/* Returns a random number between 0 and limit inclusive
 * 
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
