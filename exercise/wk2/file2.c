/* Months 4, 6, 9 and 11 have 30 days, Months 1, 3, 5, 7, 8, 10 and 12 have 31 days*/
/* Month 2 usually has 28 days except when it is leap year*/
/* Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100 */
/* But these centurial years are leap years if they are exactly divisible by 400 */
/* For example, the years 1700, 1800, and 1900 were not leap years, but the years 1600 and 2000 were*/
/* Based on these facts, evaluate the eneterd day,month,year is valid or invalid year/month/day */

#include<stdio.h>
int main()
{
   int birthMo;
   int birthDay;
   int birthYr;
   const int HIGHMO = 12;
   const int HIDAY1 = 31;
   const int HIDAY2 = 30;
   const int HIDAY3 = 29;
   const int HIDAY4 = 28;
   const int LOYEAR = 1885;
   const int HIYEAR = 2004;
   printf( "Enter your birth month ");
   scanf("%d", &birthMo);
   printf( "Enter your birth day ");
   scanf( "%d", &birthDay);
   printf( "Enter your birth year ");
   scanf("%d", &birthYr);

   if(birthYr < LOYEAR){
      printf( "No one is that old\n");}
   else if(birthYr == HIYEAR){
         printf( "You are too little to be using a computer\n");}
      else{
   printf( "Valid year\n");}
   
   if(birthMo > HIGHMO){
      printf( "Invalid month\n");}

   else if(birthMo == 1 || birthMo == 1 || birthMo == 2 || birthMo == 2){
         if(birthDay <= HIDAY4){
      printf( "Valid day\n");}
         else{
      printf( "Invalid day for month ", birthMo);} 

      else if(birthMo == 2){
      if(birthYr  == 0 && birthYr != 2000){
         if(birthDay <= HIDAY3){
                  printf( "Valid day\n");}
         else{
      printf( "Invalid day for month " , birthMo , " in " , birthYr );}}}

      else if(birthDay <= HIDAY2){
                  printf( "Valid day\n");}

          else{
      printf( "Invalid day for month " , birthMo , " in " , birthYr );}

    if(birthDay <= HIDAY1){
                printf( "Valid day"  );}
            else{
          printf( "Invalid day for month ", birthMo );
      
   return "X";
}