/* 
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * 2/5/2019
 * Assignment 4: Q4 - Card Dealer
 * ---Uncomment the test cases in main to test special hands---
 */

// Card shuffling and dealing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

//hand dealt
static int hand[5][2] = {};
static int *handPtr = hand[0];

// prototypes
void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]); // dealing doesn't modify the arrays
int checkFlush(void);
int checkStraight(void);
int checkPairs(void);
void check(void);

int main(void)
{
   // initialize deck array
   unsigned int deck[SUITS][FACES] = { 0 };

   srand(time(NULL)); // seed random-number generator

   shuffle(deck); // shuffle the deck

   // initialize suit array                       
   const char *suit[SUITS] =            
      {"Hearts", "Diamonds", "Clubs", "Spades"};
   
   // initialize face array                   
   const char *face[FACES] =
      {"Ace", "Two", "Three", "Four",         
       "Five", "Six", "Seven", "Eight",         
       "Nine", "Ten", "Jack", "Queen", "King"};

   deal(deck, face, suit); // deal the deck
   check();
   
   int i;
   /* test cases
   //test flush
   for(i=0;i<5;i++){
      hand[i][0]=2;
   }
   check();
   //test straight
   for(i=0;i<5;i++){
      hand[i][1]=1+i;
      printf("%d\n",hand[i][1]);
   }
   check();
   */
} 

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
   // for each of the cards, choose slot of deck randomly
   size_t card;
   for (card = 1; card <= CARDS; ++card) {
      size_t row; // row number
      size_t column; // column number

      // choose new random location until unoccupied slot found
      do {                                                        
         row = rand() % SUITS;                                   
         column = rand() % FACES;                             
      } while(wDeck[row][column] != 0); // end do...while

      // place card number in chosen slot of deck
      wDeck[row][column] = card;
   } 
}

// deal cards in deck
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[])
{
   // deal each of the cards
   size_t card;
   for (card = 1; card <= 5; ++card) {
      size_t row;
      // loop through rows of wDeck
      for (row = 0; row < SUITS; ++row) {
         size_t column;
         // loop through columns of wDeck for current row
         for (column = 0; column < FACES; ++column) {
            // if slot contains current card, display card
            if (wDeck[row][column] == card) {
	       *handPtr = row;
	       handPtr++;
	       *handPtr = column;
	       handPtr++;
               printf("%5s of %-8s\n", wFace[column], wSuit[row]); // 2-column format
            } 
         } 
      } 
   }
}

// Check for flush in hand
int checkFlush(void){
        int i;
        int flush = 1;
        int lastSuit = hand[0][0];
        for(i=0;i<5;i++){
                if(hand[i][0]!=lastSuit){ // check for flush
                flush = 0;
                }
        }
        return flush;
}

// Check for straight
int checkStraight(void){
	int i;
	int j;
	int straight = 1;
	int cont = 1;
	int smallest = hand[0][1];
	int biggest = hand[1][1];
	//find limits
	for(i=0;i<5;i++){
		if(hand[i][1]<smallest){
			smallest = hand[i][1];
		}
		if(hand[i][1]>biggest){
			biggest = hand[i][1];
		}
	}
	// check for increasing face values
	while(cont){
		int same = smallest;
		for(j=0;j<5;j++){
			if(hand[j][1]==smallest+1){
				smallest++;
			}
		}
		if(smallest == biggest){
			cont = 0;
		}
		else if(smallest==same){
			straight = 0;
			cont = 0;
		}
	}
	return straight;
}

//check for two pairs and full house
int checkPairs(void){
	int i;
	int j;
	int firstNum = -1;
	int firstPair = 0;
	int secondPair = 0;
	for(i=0;i<5;i++){
		for(j=i+1;j<5;j++){
			if(hand[j][1]==hand[i][1]){
				if(hand[j][1]==firstNum){
					firstPair++;
				}
				else if(firstNum==-1){
					firstNum = hand[j][1];
					firstPair++;
				}
				else{
					secondPair++;
				}
			}
		}
	}
	if(firstPair&&secondPair){
		if(firstPair==2||secondPair==2){
			return 2;
		}
		return 1;
	}
	return 0;	
}

//run checks for special hands
void check(void){
   int flush = checkFlush();
   int straight = checkStraight();
   int pairs = checkPairs();
   if(flush&&straight){
      printf("You have a straight flush!\n");
   }
   else if(flush){
      printf("You have a flush.\n");
   }
   else if(straight){
      printf("You have a straight.\n");
   }
   if(pairs==1){
      printf("You have two pairs.\n");
   }
   else if(pairs==2){
      printf("You have a full house!\n");
   }
}
