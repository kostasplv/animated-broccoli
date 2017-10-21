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
			//heapSort(indx->root,indx->root_num);
			return 1;
		}
        int found=-1;
        found=insertionSort(indx->root,indx->root_num);
       // heapSort(indx->root,indx->root_num);
        found=binary_search(str,indx->root,indx->root_num);
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
		return ;
	}
	insertionSort(node->children,node->child_num);
    int found=binary_search(str,node->children,node->child_num);
	insert_node(node->children[found],str1);	//PHGAINW ANADROMIKA APO TO NODE POU VRISKOMAI STO PAIDI//
}

int delete_ngram(Index* indx)
{
	return 1;
}

char* search(Index* indx,char* phrase)
{
	int i,flag=0;;
	char *first_word ;
	char *rest_phrase=NULL;
	char** result=malloc(sizeof(char*));
	int string_counter=-1;
	first_word=strtok(phrase," ");     	//PAIRNOUME THN PRWTH LEKSH THS PHRASHS//
	int found=-1;
	while(1)
	{
		if(rest_phrase==NULL)
		{
			rest_phrase = strtok(NULL,"");			//PAIRNOUME THN UPOLOIPH PHRASH//3
		}
		if(rest_phrase==NULL && flag==1)	//H PERIPTWSH AUTH AFORA OTAN MAS DINETAI FRASH ME >=2 LEKSEIS.TO FLAG MAS PROSTATEUEI SE PERIPTWSH POU STO QUESTION DOTHEI MONO MIA LEKSH//
		{
			break;			//H PHRASH TELEIWSE,EPOMENWS KAI H SEARCH//
		}
		flag=1;				//AN TO FLAG==1 SHMAINEI OTI EXEI SCANARISTEI ESTW KAI MIA LEKSH APO THN FRASH//
		char *str2;
		if(rest_phrase!=NULL)
		{
			str2=malloc(strlen(rest_phrase)+1);
			strcpy(str2,rest_phrase);
		}
		found=-1;
		found=binary_search(first_word,indx->root,indx->root_num);		//PSAXNOUME NA VROUME AN H EPILEGMENH LEKSH VRISKETAI STO ROOT//
		if(found==-1)			//AN DEN UPARXEI STO ROOT SUNEXIZOUME STHN EPOMENH//
		{
			first_word=strtok(rest_phrase," ");
			rest_phrase = strtok(NULL,"");
			continue;
		}
		else				//AN UPARXEI STO ROOT H PRWTH LEKSH//
		{
			char* subphrase;
			int flag=0;
			subphrase=malloc(strlen(first_word)+1);
			strcpy(subphrase,first_word);
			if(indx->root[found]->is_final=='Y')
			{
				int found1=-1;

				for(i=0;i<=string_counter;i++)
				{
					if(!strcmp(result[i],subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
					{
						found1=i;
						break;
					}
				}
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
				}
			}
			search_node(indx->root[found],rest_phrase,subphrase,result,&string_counter);			//AN UPARXEI STO ROOT TOTE ANADROMIKA PHGAINOUME STA PAIDIA//
			first_word=strtok(str2," ");
			rest_phrase = strtok(NULL,"");
			free(subphrase);
		}
	}
	if(string_counter==-1)		//SE PERIPTWSH POU KAMIA LEKSH DEN VRETHEI EPISTREFOUME -1//
	{
		return "-1";
	}
	char* ready_phrase=malloc(strlen(result[0]));		//FTIAXNOUME THN LEKSH POU THA STEILW STHN MAIN GIA NA EKTUPWTHEI//
	strcpy(ready_phrase,result[0]);
	for(i=1;i<=string_counter;i++)
	{
		ready_phrase=realloc(ready_phrase,strlen(ready_phrase)+strlen(result[i])+2);
		strcat(ready_phrase,"|");
		strcat(ready_phrase,result[i]);
		free(result[i]);
	}
	free(result);
	return ready_phrase;
}
void search_node(trie_node* node,char* phrase,char* subphrase,char** result,int *length)
{
	char *str=strtok(phrase," ");
	char* str1=strtok(NULL,"");
	int found=-1,i;
	found=binary_search(str,node->children,node->child_num);
	if(found==-1 )return ;			//AN H PRWTH LEKSH THS PHRASHS POU MAS HRTHE DEN VRETHEI STO TRIE EPISTREFOUME PISW//
	if(found!=-1 && str1==NULL)		//AN VREI THN LEKSH KAI META DEN EXEI ALLH LEKSH EPISHS H ANADROMH TELEIWNEI//
	{
		subphrase=realloc(subphrase,strlen(subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(subphrase," ");
		strcat(subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
				if(!strcmp(result[i],subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
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
					result[*length]=malloc(strlen(subphrase)+1);
					strcpy(result[*length],subphrase);
				}
				else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
				{
					(*length)++;
					result=realloc(result,(*length)*sizeof(char*));
					result[*length]=malloc(strlen(subphrase)+1);
					strcpy(result[*length],subphrase);
				}
			}
		}
	}
	if(found!=-1 && str1!=NULL)		//AN VREI THN LEKSH KAI META EXEI ALLH LEKSH SUNEXIZOUME STO EPOMENO EPIPEDO THS ANADROMHS MAS//
	{
		subphrase=realloc(subphrase,strlen(subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(subphrase," ");
		strcat(subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
				if(!strcmp(result[i],subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
				{
					found1=i;
					break;
				}
			}
			if(found1==-1 || *length==-1)			//AUTO SHMAINEI OTI DEN VRIKE THN LEKSH STO PINAKA RESULT//
			{
				if(*length==-1)		//AUTO SHMAINEI OTI DEN EXEI MPEI AKOMA STRING STON PINAKA//
				{
					(*length)++;
					result[*length]=malloc(strlen(subphrase)+1);
					strcpy(result[*length],subphrase);

				}
				else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
				{
					(*length)++;
					result=realloc(result,(*length+1)*sizeof(char*));
					result[*length]=malloc(strlen(subphrase)+1);
					strcpy(result[*length],subphrase);
				}
			}
		}
		search_node(node->children[found],str1,subphrase,result,length);		//KALOUME ANADROMIKA THN SUNARTHSH ME TO SWSTO PAIDI POU VRETHIKE//
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