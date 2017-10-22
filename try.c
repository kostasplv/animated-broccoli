#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main ()
{
	char* x,*y;
	char *first_word ;
	char *rest_phrase=NULL;
	x=malloc(10*sizeof(char));
	y=malloc(10*sizeof(char));
	strcpy(x,"as as ds");
	first_word=strtok(x," ");
	rest_phrase=strtok(NULL,"");
	strcpy(y,rest_phrase);
	printf("x=%s\ny=%s\nfirt=%s\nrest=%s\n",x,y,first_word,rest_phrase);
	//free(x);
	//printf("x=%s\ny=%s\nfirt=%s\nrest=%s\n",x,y,first_word,rest_phrase);
	first_word=strtok(rest_phrase," ");
free(x);
free(y);
	//strcpy(r,x);
	//r=&x;
	//y=x;
   
   return(0);
}
