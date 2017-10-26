#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ngrams.h"
#include <time.h>

Index* init_trie()
{
	Index *trie;
	int i;
	trie = malloc(sizeof(Index));
	trie->root_size = 100;
	trie->root = malloc(trie->root_size * sizeof(trie_node*));
	for (i = 0; i < trie->root_size; i++)
	{
		trie->root[i] = NULL;
	}
	trie->root_num = 0;
	return trie;

}

trie_node* create_trie_node() {
	trie_node* node;
	node = malloc(sizeof(trie_node));
	node->word = NULL;
	node->node_size = 20;
	node->children = malloc(node->node_size * sizeof(trie_node *));
	int i = 0;
	for (i = 0; i < node->node_size; i++) {
		node->children[i] = NULL;
	}
	node->is_final = 'N';				//  N=no , Y=yes  //
	node->child_num = 0;
	return node;
}
int binary_search(char* phrase,trie_node** node,int length)
{
	 int c, first, last, middle, n, search, array[100];
	 if(phrase==NULL)return -1;
	 first = 0;
	 last = length - 1;
	 middle = (first+last)/2;
	 while (first <= last)
	 {
		 if ((strcmp(node[first]->word ,phrase))==0)
			 	 return first;
		 if ((strcmp(node[last]->word ,phrase))==0)
			 	 return last;
	   if ((strcmp(node[middle]->word ,phrase))<0)
	         first = middle + 1;
	      else if ((strcmp(node[middle]->word ,phrase))==0)
	      {
	    	  return middle;
	         break;
	      }
	      else
	         last = middle - 1;

	      middle = (first + last)/2;
	 }
	 if (first > last)
		 return -1;
}
int insert_ngram(Index *indx, char *phrase)
{
	//printf("phrase=%s\n",phrase);
	char *str = strtok(phrase, " ");
	int i = 0;
	int found = -1;
	found=binary_search(str,indx->root,indx->root_num);
	if (found == -1)	//den vrethike i leksh sto root//
	{
		//clock_t begin = clock();
		if (indx->root_size == indx->root_num) //an o pinakas root einai gematos kanoume realloc(diplasiazoume)//
		{
			indx->root_size *= 2;
			indx->root = realloc(indx->root,indx->root_size * sizeof(trie_node));
		}
		indx->root_num++;
		indx->root[indx->root_num - 1] = create_trie_node();
		indx->root[indx->root_num - 1]->word=malloc(strlen(str)+1);
		strcpy(indx->root[indx->root_num - 1]->word, str);
		char *str1 = strtok(NULL, "");
		if (str1 == NULL) //an exei mono mia leksh h psrash//
		{
			indx->root[indx->root_num - 1]->is_final = 'Y';
			insertionSort(indx->root,indx->root_num);
			//BinaryInsertionSort(indx->root,indx->root_num);
			//heapSort(indx->root,indx->root_num);
			return 1;
		}
        int found=-1;
    	//clock_t begin = clock();
        //found=BinaryInsertionSort(indx->root,indx->root_num);
        //printf("found=%d\n",found);
    	//clock_t end = clock();
    	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    	//printf("\n22Binary insertion time  %f\n",time_spent);
    	//begin = clock();
        found=insertionSort(indx->root,indx->root_num);
       // end = clock();
       // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    	//printf("insertion time  %f\n",time_spent);
       // printf("\nfound=%d\n",found);
       // heapSort(indx->root,indx->root_num);
       // found=binary_search(str,indx->root,indx->root_num);
       // printf("found=%d\n",found);
		insert_node(indx->root[found],str1);

		/*clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("time before found  %f\n",time_spent);*/
	}
	else //to phrase uparxei sto root//
	{
		char *str1 = strtok(NULL, "");
		if (str1 == NULL) //an exei mono mia leksh h psrash//
		{
			indx->root[found]->is_final = 'Y';
			return 1;
		}

		insert_node(indx->root[found],str1);
	}
	/*for(i=0;i<indx->root_num;i++)		//PRINT VOITHITIKH GIA EMAS//
	{
        if(indx->root[i]->is_final=='Y')
            printf("%s1\n",indx->root[i]->word);
        else
            printf("%s\n",indx->root[i]->word);
		print_trie(indx->root[i],0);
    }*/
}
void insert_node(trie_node* node,char* phrase)		//anadromikh sunarthsh gia insert
{
	int i;
	char *str = strtok(phrase, " ");		//pairnoume thn prwth leksh apo thn phrash pou theloume na valoume //
	char *str1 = strtok(NULL, "");		//pairnoume thn upoloiph frash ektos ths parapanw lekshs//
	//printf("str=%s str1=%s\n",str,str1);
	for(i=0;i<node->child_num;i++)			//ELENXOUME AN UPARXEI H LEKSH POU PHRAME SE KAPOIO PAIDI TOU KOMVOU POU VRISKOMASTE//
	{
		if(!strcmp(str,node->children[i]->word))
		{
            if(str1==NULL)
            {
                node->children[i]->is_final='Y';
                return;
            }
			insert_node(node->children[i],str1);
			return ;		//AN UPARXEI TERMATIZOUME EDW//
		}
	}
	node->child_num++;			//ALLIWS AUKSANOUME METRHTH PAIDIWN KAI FTIAXNOUME KAINOURGIO PAIDI(NODE)//
    if(node->child_num==node->node_size)
    {
        node->node_size*=2;
        node->children=realloc(node->children,node->node_size*sizeof(trie_node *));
    }
	node->children[node->child_num-1]=create_trie_node();
	node->children[node->child_num-1]->word=malloc(strlen(str)+1);
	strcpy(node->children[node->child_num-1]->word,str);	//ANTIGRAFOUME TO STRING POU PHRAME PARAPANW MESA STO NODE//
	if(str1==NULL)
	{
        node->children[node->child_num-1]->is_final='Y';
        insertionSort(node->children,node->child_num);
        //BinaryInsertionSort(node->children,node->child_num);
		return ;
	}

    int found=-1;
	found=insertionSort(node->children,node->child_num);
	found=binary_search(str,node->children,node->child_num);
	//printf("\ninsertion time  %f\n",time_spent);
	//found=binary_search(str,node->children,node->child_num);
	//printf("found=%d\n",found);
	insert_node(node->children[found],str1);	//PHGAINW ANADROMIKA APO TO NODE POU VRISKOMAI STO PAIDI//
}
int delete_ngram(Index* indx,char *phrase)
{
    char *str=strtok(phrase," ");
    char *str1=strtok(NULL,"");
	int found = -1;
	found=binary_search(str,indx->root,indx->root_num);
	if(found==-1)
	{
        return 0;
	}
	else
	{
        if(str1==NULL)
        {
            if(indx->root[found]->is_final=='Y')
            {
                if(indx->root[found]->child_num==0)
                {
                    free(indx->root[found]->word);
                    indx->root[found]->word=NULL;
					free(indx->root[found]->children);
					indx->root[found]->children=NULL;
                    free(indx->root[found]);
                    indx->root[found]=NULL;
                    int i;
                    for(i=found+1;i<indx->root_num;i++)
                    {
                        indx->root[i-1]=indx->root[i];
                        indx->root[i]=NULL;
                    }
                    indx->root_num=indx->root_num-1;
                    return 1;
                }
                else
                {
                    indx->root[found]->is_final='N';
                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            int chc;
            chc=delete_node(indx->root[found],str1);
            if(chc==2)
            {
                if(indx->root[found]->is_final=='N')
                {
                    if(indx->root[found]->child_num==0)
                    {
                        free(indx->root[found]->word);
                        indx->root[found]->word=NULL;
						free(indx->root[found]->children);
						indx->root[found]->children=NULL;
                        free(indx->root[found]);
                        indx->root[found]=NULL;
                        int i;
                        for(i=found+1;i<indx->root_num;i++)
                        {
                            indx->root[i-1]=indx->root[i];
                            indx->root[i]=NULL;
                        }
                        indx->root_num=indx->root_num-1;
                        return 1;
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else if(chc==1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
	}
	return 1;
}
int delete_node(trie_node *node,char *phrase)
{
    int found=-1;
    char *str=strtok(phrase," ");
    char *str1=strtok(NULL,"");
    found=binary_search(str,node->children,node->child_num);
    if(found==-1)
    {
        return 0;
    }
    else
    {
        if(str1==NULL)
        {
            if(node->children[found]->is_final=='Y')
            {
                if(node->children[found]->child_num==0)
                {
                    free(node->children[found]->word);
                    node->children[found]->word=NULL;
					free(node->children[found]->children);
					node->children[found]->children=NULL;
                    free(node->children[found]);
                    node->children[found]=NULL;
                    int i;
                    for(i=found+1;i<node->child_num;i++)
                    {
                        node->children[i-1]=node->children[i];
                        node->children[i]=NULL;
                    }
                    node->child_num=node->child_num-1;
                    return 2;
                }
                else
                {
                    node->children[found]->is_final='N';
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            int chc;
            chc=delete_node(node->children[found],str1);
            if(chc==2)
            {
                if(node->children[found]->is_final=='N')
                {
                    if(node->children[found]->child_num==0)
                    {
                        free(node->children[found]->word);
                        node->children[found]->word=NULL;
						free(node->children[found]->children);
						node->children[found]->children=NULL;
                        free(node->children[found]);
                        node->children[found]=NULL;
                        int i;
                        for(i=found+1;i<node->child_num;i++)
                        {
                            node->children[i-1]=node->children[i];
                            node->children[i]=NULL;
                        }
                        node->child_num=node->child_num-1;
                        return 2;
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else if(chc==1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}
char* search(Index* indx,char* phrase)
{
	int i,flag=0,flag1=0,c=0,c1=0,c2=0;
	char *first_word ;
	char *rest_phrase=NULL;
	char** result=malloc(sizeof(char*));
	//printf("phrase=%s\n",phrase);
	int string_counter=-1;
	//first_word=strtok(phrase," ");     	//PAIRNOUME THN PRWTH LEKSH THS PHRASHS//
	//rest_phrase = strtok(NULL,"");
	int found=-1;
	char *str2=NULL, *subphrase=NULL, *tempString;
	char *temp;
	temp=malloc(strlen(phrase)+1);
	str2=malloc(strlen(phrase)+1);
	strcpy(temp,phrase);
	//str2=NULL;
	//printf("edw\n");
	int str2_flag=0,temp_flag=0;
	while(1)
	{
		if(str2_flag==0 && temp_flag==0)
		{
			first_word=strtok(temp," ");
			rest_phrase = strtok(NULL,"");			//PAIRNOUME THN UPOLOIPH PHRASH//3
			strcpy(str2,rest_phrase);
			temp_flag=1;
		}
		if(((str2==NULL && str2_flag==0) || (temp==NULL && temp_flag==0)) && flag==1)	//H PERIPTWSH AUTH AFORA OTAN MAS DINETAI FRASH ME >=2 LEKSEIS.TO FLAG MAS PROSTATEUEI SE PERIPTWSH POU STO QUESTION DOTHEI MONO MIA LEKSH//
		{
			if(temp_flag==1)
			{
				free(temp);
			}
			if(str2_flag==1)
			{
				free(str2);
			}
			//printf("malloc=%d\nfree1=%d\nfree2=%d\n",c,c1,c2);
			break;			//H PHRASH TELEIWSE,EPOMENWS KAI H SEARCH//
		}
		//printf("3edw\n");
		if(((str2!=NULL && str2_flag==0) || (temp!=NULL && temp_flag==0)) && flag==1)
		{
			if(str2_flag==1)
			{
				free(str2);
				first_word=strtok(temp," ");
				rest_phrase = strtok(NULL,"");
				temp_flag=1;
				if(rest_phrase!=NULL)
				{
					str2=malloc(strlen(rest_phrase)+1);
					strcpy(str2,rest_phrase);
					str2_flag=0;
				}
				else
				{
					str2=NULL;
					str2_flag=0;
				}
			}
			else if(temp_flag==1)
			{
				free(temp);
				first_word=strtok(str2," ");
				rest_phrase = strtok(NULL,"");
				str2_flag=1;
				if(rest_phrase!=NULL)
				{
					temp=malloc(strlen(rest_phrase)+1);
					strcpy(temp,rest_phrase);
					temp_flag=0;
				}
				else
				{
					temp=NULL;
					temp_flag=0;
				}
			}
			flag1=1;
		}
		flag=1;
		//printf("\nmeta\nfirst=%s\nrest=%s\nstr2=%s\ntemp=%s\n",first_word,rest_phrase,str2,temp);
		found=-1;
		found=binary_search(first_word,indx->root,indx->root_num);		//PSAXNOUME NA VROUME AN H EPILEGMENH LEKSH VRISKETAI STO ROOT//
		if(found==-1)			//AN DEN UPARXEI STO ROOT SUNEXIZOUME STHN EPOMENH//
		{
			//printf("4edw\n");
			continue;
		}
		else				//AN UPARXEI STO ROOT H PRWTH LEKSH//
		{
			//printf("5edw\n");
			int flag=0;
			//printf("firs=%s\n",first_word);
			subphrase=malloc(strlen(first_word)+1);
			strcpy(subphrase,first_word);
			//printf("00edw\n");
			if(indx->root[found]->is_final=='Y')
			{
				int found1=-1;

				for(i=0;i<=string_counter;i++)
				{
					//printf("%d\n",i);
					//printf("%s\n",subphrase);
					//printf("result[%d]=%s\nsubphrase=%s\n",i,result[i],subphrase);
					if(!strcmp(result[i],subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
					{
						found1=i;
						break;
					}
				}
				//printf("5000edw\n");
				if(found1==-1 || string_counter==-1)			//AUTO SHMAINEI OTI DEN VRIKE THN LEKSH STO PINAKA RESULT//
				{
					if(string_counter==-1)		//AUTO SHMAINEI OTI DEN EXEI MPEI AKOMA STRING STON PINAKA//
					{
						string_counter++;
						result[string_counter]=malloc(strlen(subphrase)+1);
						strcpy(result[string_counter],subphrase);

					}
					else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
					{
						string_counter++;
						result=realloc(result,(string_counter+1)*sizeof(char*));
						result[string_counter]=malloc(strlen(subphrase)+1);
						strcpy(result[string_counter],subphrase);

					}
				//	printf("0result[%d]=%s\n",string_counter,result[string_counter]);
					//printf("result=%s\n",subphrase);
				}

			}
			//printf("7edw----%d\n",string_counter);
			search_node(indx->root[found],rest_phrase,&subphrase,&result,&string_counter);			//AN UPARXEI STO ROOT TOTE ANADROMIKA PHGAINOUME STA PAIDIA//
			free(subphrase);
			subphrase=NULL;
			//printf("6edw----%d\n",string_counter);
		}
	}
	if(string_counter==-1)		//SE PERIPTWSH POU KAMIA LEKSH DEN VRETHEI EPISTREFOUME -1//
	{
		free(result);
		return "-1";
	}
	char* ready_phrase=malloc(strlen(result[0])+1);		//FTIAXNOUME THN LEKSH POU THA STEILW STHN MAIN GIA NA EKTUPWTHEI//
	strcpy(ready_phrase,result[0]);
	for(i=1;i<=string_counter;i++)
	{
		ready_phrase=realloc(ready_phrase,strlen(ready_phrase)+strlen(result[i])+2);
		strcat(ready_phrase,"|");
		strcat(ready_phrase,result[i]);
		//if(result[i]==NULL)continue;

	}
	for(i=0;i<=string_counter;i++)
	{
		free(result[i]);
		result[i]=NULL;
	}
	free(result);
	result=NULL;

	return ready_phrase;
}
void search_node(trie_node* node,char* phrase,char** subphrase,char*** result,int *length)
{
	//printf("55edw----%d\n",*length);
	char *str=strtok(phrase," ");
	char* str1=strtok(NULL,"");
	//printf("56edw\n");
	int found=-1,i;
	//printf("str=%s\nstr1=%s\n",str,str1);
	found=binary_search(str,node->children,node->child_num);
	//printf("57edw\n");
	if(found==-1 )return ;			//AN H PRWTH LEKSH THS PHRASHS POU MAS HRTHE DEN VRETHEI STO TRIE EPISTREFOUME PISW//
	if(found!=-1 && str1==NULL)		//AN VREI THN LEKSH KAI META DEN EXEI ALLH LEKSH EPISHS H ANADROMH TELEIWNEI//
	{
		//printf("5edw\n");
		*subphrase=realloc(*subphrase,strlen(*subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(*subphrase," ");
		strcat(*subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
				//printf("%s\n",*subphrase);
				if(!strcmp((*result)[i],*subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
				{
					found1=i;
					break;
				}
			}
			if(found1==-1 || *length==-1)			//AUTO SHMAINEI OTI DEN VRIKE THN LEKSH STO PINAKA RESULT//
			{
				if((*length)==-1)		//AUTO SHMAINEI OTI DEN EXEI MPEI AKOMA STRING STON PINAKA//
				{
					(*length)++;
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					strcpy((*result)[*length],*subphrase);
				}
				else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
				{
					(*length)++;
					(*result)=realloc((*result),((*length)+1)*sizeof(char*));
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					strcpy((*result)[*length],*subphrase);
				}
			//	printf("1result[%d]=%s\n",*length,(*result)[*length]);
			}
		}
	}
	if(found!=-1 && str1!=NULL)		//AN VREI THN LEKSH KAI META EXEI ALLH LEKSH SUNEXIZOUME STO EPOMENO EPIPEDO THS ANADROMHS MAS//
	{
		//printf("4edw\n");
		*subphrase=realloc(*subphrase,strlen(*subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(*subphrase," ");
		strcat(*subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
				////printf("%d\n",i);
				//printf("%s\n",*subphrase);
				//if(((*result))[i]==NULL)continue;
				//printf("result[%d]=%s\nsubphrase=%s\n",i,((*result))[i],*subphrase);
				//printf("for=%s\n",*subphrase);
				if(!strcmp((*result)[i],*subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
				{
					found1=i;
					break;
				}
			}
			//printf("found=%d\n*length=%d\n",found1,*length);
			//printf("atfor=%s\n",*subphrase);
			if(found1==-1 || *length==-1)			//AUTO SHMAINEI OTI DEN VRIKE THN LEKSH STO PINAKA RESULT//
			{
				if(*length==-1)		//AUTO SHMAINEI OTI DEN EXEI MPEI AKOMA STRING STON PINAKA//
				{
					(*length)++;
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					strcpy(*(result[*length]),*subphrase);

				}
				else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
				{
					//printf("atfor=%s\n",*subphrase);
					(*length)++;
					//printf("atfor=%s\n",*subphrase);
					(*result)=realloc((*result),((*length)+1)*sizeof(char*));
					//printf("atfor=%s\n",*subphrase);
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					//printf("sub=%s\n",*subphrase);
					strcpy((*result)[*length],*subphrase);
				}
				//printf("2result[%d]=%s\n",*length,(*result)[*length]);
			}
		}
		//printf("3edw----string=%d\n",*length);
		search_node(node->children[found],str1,subphrase,result,length);		//KALOUME ANADROMIKA THN SUNARTHSH ME TO SWSTO PAIDI POU VRETHIKE//
		//printf("2edw\n");
	}
	//printf("1edw\n");
}
void delete_trie(Index **indx)
{
    int i;
    for(i=0;i<(*indx)->root_num;i++)
    {
        delete_helper((*indx)->root[i]);
        free((*indx)->root[i]->word);
        (*indx)->root[i]->word=NULL;
        free((*indx)->root[i]->children);
        (*indx)->root[i]->children=NULL;
        free((*indx)->root[i]);
        (*indx)->root[i]=NULL;
    }
    free((*indx)->root);
    (*indx)->root=NULL;
    free((*indx));
    (*indx)=NULL;
}
void delete_helper(trie_node *node)
{
    if(!node->child_num) return;
    int i;
    for(i=0;i<node->child_num;i++)
    {
        delete_helper(node->children[i]);
        free(node->children[i]->word);
        node->children[i]->word=NULL;
        free(node->children[i]->children);
        node->children[i]->children=NULL;
        free(node->children[i]);
        node->children[i]=NULL;
    }
}
void heapSort(trie_node** arr, int n)
{
    // Build heap (rearrange array)
	trie_node* temp;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
    	temp=arr[i];
    	arr[i]=arr[0];
    	arr[0]=temp;
       // swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
void heapify(trie_node** arr, int n, int i)
{
	trie_node* temp;
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && (strcmp(arr[l]->word , arr[largest]->word)>0))
        largest = l;

    // If right child is larger than largest so far
    if (r < n && (strcmp(arr[r]->word , arr[largest]->word)>0))
        largest = r;

    // If largest is not root
    if (largest != i)
    {
       // swap(arr[i], arr[largest]);
    	temp=arr[i];
    	arr[i]=arr[largest];
    	arr[largest]=temp;
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
void change_trie(Index* indx,trie_node* node,char* phrase)		//ektupwnei to dentro anadromika(komvos->prwto paidi komvou->prwto paidio paidiou komvou->...->deuterp paidi komvou->deutero paidi paidiou komovou->....//
{
	int i;
	trie_node* temp;
	printf("\nphrase=%s\n",phrase);
	if(phrase==NULL)return;
	char *str=strtok(phrase,"|");
	printf("str=%s\n",str);
	char *str1=strtok(NULL,"");
	char* string;
	if(str1!=NULL)
	{
		string=malloc(strlen(str1)+2);
		strcpy(string,str1);
	}
	char *str2=strtok(str," ");
	char *str3=strtok(NULL,"");
	printf("str=%s\nstr1=%s\nstr2=%s\nstr3=%s\n",str,str1,str2,str3);
	if(str3==NULL)
	{
		if(str1==NULL)return;
		change_trie(indx,NULL,str1);
		strtok(string,"|");
		change_trie(indx,NULL,strtok(NULL,""));
		//printf("---str=%s\nstr1=%s\nstr2=%s\nstr3=%s\n",str,str1,str2,str3);
		//printf("\nphrase=%s\n",string);
		//if(str1!=NULL)change_trie(indx,NULL,str1);
	}
	else
	{

		if(node==NULL)
		{
			int found=binary_search(str2,indx->root,indx->root_num);
			temp=indx->root[found];
		}
		else
		{
			int found=binary_search(str2,node->children,node->child_num);
			temp=node->children[found];
		}
		change_trie(indx,temp,str3);
	}
/*
	if(indx->root[found]->is_final=='Y' && indx->root[found]->visited==1)
	{
		indx->root[found]->visited=0;
	}
	for(i=0;i<node->child_num;i++)
	{
		int j;
		for(j=0;j<tabs;j++)
            printf("\t");
        if(node->children[i]->is_final=='Y')
            printf("%s1 , i=%d\n",node->children[i]->word,i);
        else
            printf("%s , i=%d\n",node->children[i]->word,i);
        if(node->child_num==0)
            return;
		print_trie(node->children[i],tabs);
	}*/
}
void print_trie(trie_node* node,int tabs)		//ektupwnei to dentro anadromika(komvos->prwto paidi komvou->prwto paidio paidiou komvou->...->deuterp paidi komvou->deutero paidi paidiou komovou->....//
{
	int i;
	tabs++;
	//printf("word=%s\n",node->word);
	for(i=0;i<node->child_num;i++)
	{
		//printf("child_num=%d\nis_final=%c\nnode_size=%d\nword=%s\n",node->child_num,node->is_final,node->node_size,node->word);
		int j;
		for(j=0;j<tabs;j++)
            printf("\t");
        if(node->children[i]->is_final=='Y')
            printf("%s1 , i=%d\n",node->children[i]->word,i);
        else
            printf("%s , i=%d\n",node->children[i]->word,i);
        if(node->child_num==0)
            return;
		print_trie(node->children[i],tabs);
	}
}
int insertionSort1(trie_node** a, int n)
{
    int i, loc, j, k, selected;
    trie_node* temp;
    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        temp = a[i];

        // find location where selected sould be inseretd
        loc = binarySearch1(a,temp,0,j);
        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }
  //  printf("location=%d---j=%d\n",loc,j);
    return loc;
}
int BinaryInsertionSort (trie_node** a, int n)
{
    register int i, m;
    int hi, lo;
    trie_node* tmp;

    for (i = 1; i < n; i++)
    {
        lo = 0, hi = i;
        m = i / 2;

        do {
            if ((strcmp(a[i]->word , a[m]->word))>0)
            {
                lo = m + 1;
            } else if ((strcmp(a[i]->word , a[m]->word))<0) {
                hi = m;
            } else
                break;

            m = lo + ((hi - lo) / 2);
        } while (lo < hi);

        if (m < i) {
            tmp = a[i];
            memmove (a + m + 1, a + m, sizeof (trie_node*) * (i - m));
            a[m] = tmp;
        }
    }
    if(i-2<0)return 0;
    return i-2;
    printf("found=%d--%d--%d--%d\n",m,i,lo,hi);
}
/*int BinarySearch (trie_node** a, int low, int high, char* key)
{
    int mid;

    if (low == high)
        return low;

    mid = low + ((high - low) / 2);

    if (strcmp(key , a[mid]->word)>0)
        return BinarySearch (a, mid + 1, high, key);
    else if (strcmp(key , a[mid]->word)<0)
        return BinarySearch (a, low, mid, key);

    return mid;
}
int BinaryInsertionSort (trie_node** a, int n)
{
    int ins, i, j;
    trie_node* tmp;

    for (i = 1; i < n; i++) {
        ins = BinarySearch (a, 0, i, a[i]->word);
        if (ins < i) {
            tmp = a[i];
            for (j = i - 1; j >= ins; j--)
                a[j + 1] = a[j];
            a[ins] = tmp;
        }
    }

    return i-2;
}*/
int binarySearch1(trie_node** a, trie_node* item, int low, int high)
{
    if (high <= low)
        return (strcmp(item->word , a[low]->word)>0)?  (low + 1): low;

    int mid = (low + high)/2;

    if(strcmp(item->word, a[mid]->word)==0)
        return mid+1;

    if(strcmp(item->word , a[mid]->word)>0)
        return binarySearch1(a, item, mid+1, high);
    return binarySearch1(a, item, low, mid-1);
}
int insertionSort(trie_node** array, int length)
{
   int i, j;
   trie_node* temp;
 /*  if(length>=2)
   {
	   if((strcmp(array[length-1]->word,array[length-2]->word))>0)
	   {
		   return length-1;
	   }
	   else  if((strcmp(array[length-1]->word,array[0]->word))<0)
	   {
		   temp=array[length-1];
		   for(i=length-2;i>=0;i--)
		   {
			   array[i]=array[i+1];
		   }
		   array[0]=temp;
		   return 0;
	   }
   }*/
   for (i = 1 ; i < length ; i++)
   {
       j = i;

       while ( j > 0 && (strcmp(array[j]->word , array[j-1]->word))<0)
       {
    	   temp=array[j];
    	   array[j]=array[j-1];
    	   array[j-1]=temp;
    	   j--;
       }
    }
   return j;
}
void children_sort(trie_node **children,int child_num)
{
    //printf("i am here\n");
    int i=0,j=0;
    for(i=0;i<child_num-1;i++)
    {
        for(j=i+1;j<child_num;j++)
        {
            if (strcmp(children[i]->word, children[j]->word) > 0)
            {
                trie_node *temp;
                temp=children[i];
                children[i]=children[j];
                children[j]=temp;
            }
        }
    }
}
