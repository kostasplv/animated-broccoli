#include <stdio.h>
#include "ngrams.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t begin = clock();
	int j,i;
	Index *Trie;
	Trie=init_trie();
	char *phrase;
	FILE* init_f,*query_f;
	int icheck;
	int qcheck;
	icheck=0;
	qcheck=0;
    if(argc!=5)
    {
        printf("wrong number of arguements\n");
        return -1;
    }
    else
    {
        for(i=1;i<argc;i=i+2)/*gets the arguements from command line*/
        {
            if(!strcmp(argv[i],"-i"))
            {
                init_f=fopen(argv[i+1],"r");
                if(init_f==NULL)
                {
                    printf("error opening initialisation file\n");
                    return -1;
                }
                printf("init_f %s\n",argv[i+1]);
                icheck=1;
            }
            else if(!strcmp(argv[i],"-q"))
            {
                query_f=fopen(argv[i+1],"r");
                if(query_f==NULL)
                {
                    printf("error opening query file\n");
                    return -1;
                }
                printf("query_f %s\n",argv[i+1]);
                qcheck=1;
            }
        }

    }
    if(icheck==0 || qcheck==0)
    {
        printf("wrong arguements\n");
        return -1;
    }
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
		printf("%d\n",cnt);
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

        if(!strcmp(command,"A")) //entoli gia prosthesi n-gram sto trie
        {
           insert_ngram(Trie,topass);
        }
        else if(!strcmp(command,"D")) //entoli gia diagrafi n-gram apo to trie
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
        else if(!strcmp(command,"Q")) //entoli gia anazitisi engrams se dosmeni frasi
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
	fclose(f);
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
