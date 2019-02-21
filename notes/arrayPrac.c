#include<stdio.h>

static int n = 0;
static char c = 'q';
static char carr[] = "yer";
static char* carr2[5];

int main(void){
	printf("%d\n",n);
	n++;
	printf("%d\n",n);
	c = 't';
	printf("%c\n",c);
	printf("%c\n",c);
	printf("%c\n",carr);
	printf("%s\n",carr);
	char yote[] = "yo mama";
	printf("%s\n",yote);
	printf("%p\n",yote);
	carr2[0] = yote;
	printf("%p\n",carr2[0]);
	printf("%s\n",carr2[0]);
	return 0;
}
