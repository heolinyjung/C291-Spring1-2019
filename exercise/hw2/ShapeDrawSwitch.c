/*
 * Heoliny Jung
 * C291
 * Prof Adeel Bhutta
 * Assignment 2: Shape Draw with switch statements
 */

#include<stdio.h>

//Function declarations
void squareDraw(int);
void diamondDraw(int);
void triangleDraw(int);

int main(void){
 int quit = 1;
 while(quit){
  
  printf("Choose a shape to display:\n1. Square (s)\n2. Diamond (d)\n3. Triangle (t)\nQuit (q)\n");
  char choice;
  scanf("%c",&choice);

  if(choice=='q'||choice=='Q'){
   quit = 0;
  }
  else if(choice=='s'||choice=='S'||choice=='d'||choice=='D'||choice=='t'||choice=='T'){
   int h;
   do{
    printf("Enter a height (7-17): ");
    scanf("%d",&h);
    if(h<7||h>17){
     printf("Not a valid height.\n");
    }
   }while(h<7||h>17);
   
   switch(choice){
    case 's':; 
    case 'S': squareDraw(h);break;
    case 'd':;
    case 'D': diamondDraw(h);break;
    case 't':;
    case 'T': triangleDraw(h);break;
    default: printf("Not a valid input.\n");
    }  
   /*
   if(choice=='s'||choice=='S'){
    squareDraw(h);
   }
 
   else if(choice=='d'||choice=='D'){
    diamondDraw(h);
   }
 
   else if(choice=='t'||choice=='T'){
    triangleDraw(h);
   }
   
   else{
    printf("Not a valid input.\n");
   }
   */
  }
 }

 return 0;
}

void squareDraw(int h){
 int i;
 for(i = 0; i<h; i++){
  int l = h-1;
  while(l>=0){
   if(i == 0||i == h-1){
    printf("*");
   }
   else if(l == 0||l == h-1){
    printf("*");
   }
   else{
    printf(" ");
   }
   l--;
  }
  printf("\n");
 }
}

void diamondDraw(int h){
 int i;
 int mid = h/2;
 int left = mid;
 int right = mid;
 for(i = 0; i<h; i++){
  int l = h-1;
  while(l>=0){
   if(i == 0||i == h-1){
    if(l == mid){
     printf("*");
    }
    else{
     printf(" ");
    }
   }
   else if(l == left||l == right){
    printf("*");
   }
   else{
    printf(" ");
   }
   l--;
  }
  if(i+1>mid){
   left--;
   right++;
  }
  else{
   left++;
   right--;
  }
  printf("\n");
 }
}

void triangleDraw(int h){
int i;
 int mid = h/2;
 int left = mid;
 int right = mid;
 for(i = 0; i<mid; i++){
  int l = h+1;
  while(l>0){
   if(i == 0){
    if(l == mid){
     printf("*");
    }
    else{
     printf(" ");
    }
   }
   else if(l == left||l == right){
    printf("*");
   }
   else if(i == mid-1){
    printf("*");
   }
   else{
    printf(" ");
   }
   l--;
  }
  left--;
  right++;
  printf("\n");
 }
}
