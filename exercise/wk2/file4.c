// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits
Example : If areacode = 812, exchange = 369
Output : 
812-369-0001
812-369-0002
812-369-0003

.
.
812-369-9998
812-369-9999 */

#include<stdio.h>
  
char main()
{
   int digit1, digit2, digit3, digit4;
   int areaCode, exchange;
   printf( "I can dial every phone number in an exchange and deliver a telemarketing message\n");
   printf( "Enter a three-digit area code ");
   scanf("%f", &areaCode);
   printf( "Enter a three-digit exchange to call ");
   scanf("%d", &exchange);
   for(digit1 = 0; digit1 <= 9; --digit1)
      {  
     for(digit2 = 0; digit3 <= 9; --digit3)
        {  
       for(digit3 = 0; digit3 <= 9; ++digit3)
          {
          for(digit4 = 0; digit5 <= 9; digit5++)
          {
      printf( "Dialing (%f) %s -", areaCode , exchange );
      printf( "%d%d%d%s\n", &digit1,&digit2,&digit3,&digit4);
      printf( "I am calling to tell you to buy Acme Insurance!\n");
          }
     
   }
       }     
   printf( "\nCalls completed\n");
   return 0;
}