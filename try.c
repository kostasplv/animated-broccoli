#include <string.h>
#include <stdio.h>

#include <stdlib.h>


int new(char*** str)
{
	//strcpy((*str)[0],"asdad");
	strcpy(*str[0],"asdad");
}
int main ()
{
	char* x,*y;
	char **first_word ;
	char *rest_phrase=NULL;
	x=malloc(10*sizeof(char));
	y=malloc(10*sizeof(char));
	strcpy(x,"as as ds");
	first_word=malloc(sizeof(char*));
	first_word[0]=malloc(10*sizeof(char));
	new(&first_word);
	//rest_phrase=strtok(NULL,"");
	//strcpy(y,rest_phrase);
	printf("fir=%s\n",first_word[0]);
	//printf("x=%s\ny=%s\nfirt=%s\nrest=%s\n",x,y,first_word,rest_phrase);
	//free(x);
	//printf("x=%s\ny=%s\nfirt=%s\nrest=%s\n",x,y,first_word,rest_phrase);

	//strcpy(r,x);
	//r=&x;
	//y=x;
   
   return(0);
}
