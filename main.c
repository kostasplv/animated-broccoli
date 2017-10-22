#include <stdio.h>
#include "ngrams.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t begin = clock();
	int i;
	Index *Trie;
	Trie=init_trie();
	char* init_file,*query_file,*phrase;
	FILE* init_f,*query_f;
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-i"))
		{
			init_file=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(init_file==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(init_file,argv[i+1]);
		}
		if(!strcmp(argv[i],"-q"))
		{
			query_file=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(query_file==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(query_file,argv[i+1]);
		}
	}
	init_f=fopen(init_file,"r");
	query_f=fopen(query_file,"r");
	int cnt=0;
	while(1)
	{
		int phrase_size=20;
		phrase=malloc(phrase_size*sizeof(char));
		int counter=0;
		char c;
		c=fgetc(init_f);
		if(c==EOF)
			{
			free(phrase);
			break;
			}
		//printf("2.%d\n",cnt);
		while(c!=EOF && c!='\n')
		{
			if(counter==phrase_size)
			{
				phrase_size*=2;
				phrase=realloc(phrase,phrase_size*sizeof(char));
			}
			phrase[counter]=c;
			counter++;
			c=fgetc(init_f);
		}
		//printf("1.%d\n",cnt);
		if(counter==phrase_size)
		{
			phrase_size*=2;
			phrase=realloc(phrase,phrase_size*sizeof(char));
		}
		phrase[counter]='\0';
		cnt++;
		//printf("%d\n",cnt);
		//printf("phrase=%s\n",phrase);
		insert_ngram(Trie,phrase);

		free(phrase);
		phrase=NULL;
		if(c==EOF) break;
	}
	char *qphrase;
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time  %f\n",time_spent);
	printf("Telos insert\n");
	FILE* f=fopen("hello.txt","w+");
	while(1)
	{
		int phrase_size=20;
		qphrase=malloc(phrase_size*sizeof(char));
		int counter=0;
		char c;
		c=fgetc(query_f);
		if(c==EOF)
		{
			free(qphrase);
			break;
		}
		while(c!=EOF && c!='\n')
		{
			if(counter==phrase_size)
			{
				phrase_size*=2;
				qphrase=realloc(qphrase,phrase_size*sizeof(char));
			}
			qphrase[counter]=c;
			counter++;
			c=fgetc(query_f);
		}
		if(counter==phrase_size)
		{
			phrase_size*=2;
			qphrase=realloc(qphrase,phrase_size*sizeof(char));
		}
		qphrase[counter]='\0';
        char *str;
        char *str1;
        int flag=0;
        str=strtok(qphrase," ");
        str1=strtok(NULL,"");
        char *topass;
        if(str1!=NULL)
        {
        	flag=1;		//shmainei oti phrash sto Q den einai kenh//an flag=0 tote to Q einai keno//
            topass=malloc(strlen(str1)+1);
            strcpy(topass,str1);
        }
        char *command=malloc(strlen(str)+1);
        strcpy(command,str);

        if(!strcmp(command,"A"))
        {
           insert_ngram(Trie,topass);
        }
        else if(!strcmp(command,"D"))
        {
           if(delete_ngram(Trie,topass)==1)
            {
               // printf("successful\n");
            }
            else
            {
               // printf("not successful\n");
            }
        }
        else if(!strcmp(command,"F"))
        {

        }
        else if(!strcmp(command,"Q"))
        {
        	char* result=NULL;
        //	if(flag==0)strcpy(result,"-1");					//Q ME KENO PHRASE//
        	//else
        	{
        		result=search(Trie,topass);					//Q ME MH KENO PHRASE//
            	//printf("result=%s\n",result);

            	fprintf(f,"%s\n",result);
            	if(strcmp(result,"-1"))
            		if(result!=NULL)
            			free(result);
        	}
        	flag=0;
        	//free(result);
        }
        else
        {
            printf("invalid command\n");
        }
        free(command);
        command=NULL;
        free(topass);
        topass=NULL;
		free(qphrase);
		qphrase=NULL;
		if(c==EOF) break;
	}
	fclose(init_f);
	fclose(query_f);
	free(query_file);
	free(init_file);
	/*for(i=0;i<Trie->root_num;i++)		//PRINT VOITHITIKH GIA EMAS//
	{
        if(Trie->root[i]->is_final=='Y')
            printf("%s1\n",Trie->root[i]->word);
        else
            printf("%s\n",Trie->root[i]->word);
		print_trie(Trie->root[i],0);
    }*/
    delete_trie(&Trie);
}
