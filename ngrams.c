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
	 int  first, last, middle;
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
	char *str = strtok(phrase, " ");
	int found = -1;
	found=binary_search(str,indx->root,indx->root_num);
	if (found == -1)	//den vrethike i leksh sto root//
	{
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
			return 1;
		}
        int found=-1;
        found=insertionSort(indx->root,indx->root_num);
		insert_node(indx->root[found],str1);
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
}
void insert_node(trie_node* node,char* phrase)		//anadromikh sunarthsh gia insert
{
	int i;
	char *str = strtok(phrase, " ");		//pairnoume thn prwth leksh apo thn phrash pou theloume na valoume //
	char *str1 = strtok(NULL, "");		//pairnoume thn upoloiph frash ektos ths parapanw lekshs//
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
    int found=-1;
	found=insertionSort(node->children,node->child_num);
	found=binary_search(str,node->children,node->child_num);
	insert_node(node->children[found],str1);	//PHGAINOUME ANADROMIKA APO TO NODE POU VRISKOMASTE STO PAIDI//
}
int delete_ngram(Index* indx,char *phrase)// DAIGRADFEI ENA N-GRAM APO TO TRIE
{
    char *str=strtok(phrase," ");//PAIRNEI THN PRWTH LEKSH TOY N-GRAM
    char *str1=strtok(NULL,"");//EINAI TO YPOLOIPO N-GRAM XORIS THN PRWTH LEKSH
	int found = -1;
	found=binary_search(str,indx->root,indx->root_num);//PSAXNOYME THN PRWTH LEKSH STO ROOT AN DEN YPARXEI EPISTREFEI MHDEN
	if(found==-1)
	{
        return 0;
	}
	else
	{
        if(str1==NULL)//AN TO N-GRAM EINAI MONO MIA LEKSH
        {
            if(indx->root[found]->is_final=='Y')//KOITAME AN EINAI TELIKOS KOMVOS
            {
                if(indx->root[found]->child_num==0)//AN DEN EXEI PAIDIA TOTE APLA TON DIAGRAFEI
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
                else//AN EXEI PAIDIA APLA TON KANEI TO TELIKO KOMVO MH TELIKO
                {
                    indx->root[found]->is_final='N';
                    return 1;
                }
            }
            else//AN DEN EINAI TELIKOS KOMVOS TOTE DEN YPARXEI TO N-GRAM KAI EPISTREFEI MHDEN
            {
                return 0;
            }
        }
        else//AN TO N-GRAM DEN HTAN MONO MIA LEKSI TOTE KALOYME GIA TO YPOLOIPO STRING THN VOHTHITIKH SYNARTHSH delete_node
        {
            int chc;
            chc=delete_node(indx->root[found],str1);
            if(chc==2)//AN AYTI EPISTREPSEI 2 SHMAINEI OTI DIEGRAPSE TOYS KOMVOYS TWN ALLWN LEKSEWN ARA THA KOITAKSOYME NA DOYME AN MPOROYME NA DIAGRAPSOYME TON KOMVO THS PRWTHS LEKSHS
            {
                if(indx->root[found]->is_final=='N')//AN EINAI MH TELIKOS O KOMVOS THS PRWTHS LEKSHS
                {
                    if(indx->root[found]->child_num==0)//AN DEN EXEI PAIDIA TOTE TON DIAGRAFOYME
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
                    else//AN APISTREPSEI 1 SHMAINEI OTI DEN MPORESE NA DIAGRAPSEI OLOYS TOY KOMVOYS TWN ALLWN LEKSEWN ARA APLA EPISTREFEI POS EGINE EPITYXWN H DIAGRAFH
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else if(chc==1)//AN EPISTREPSEI 1 SHMAINEI PWS DEN MPORESE NA DIAGRAPSEI TOYS KOMVOYS TWN EPOMENWN LEKSEWN ARA EPISTREFEI PWS EGINE EPITYXWS H DIAGRAFH
            {
                return 1;
            }
            else//AN EPISTREPSEI MHDEN TOTE SHMAINEI OTI DEB VRIKE TO N-GRAM ARA EPISTREFEI LATHOS
            {
                return 0;
            }
        }
	}
	return 1;
}
int delete_node(trie_node *node,char *phrase)//VOHTHITIKH SYNARTHSH THS delete_ngram
{
    int counter=0;
    int size=20;
    trie_node **temp;
    int *where;
    temp=malloc(size*sizeof(trie_node *));//SE AYTON TON PINAKA KRATAME TIS DIEYTHYNSEIS TWN trie_nodes POY EXOYN WS PAIDIA TIS LEKSEIS POY PSAXNOYME
    where=malloc(size*sizeof(int));//KAI SE AYTON KRATAME THN THESH MESA STON PINAKA children TWN trie_nodes OPOY EINAI OI LEKSEIS
    int found=-1;
    char *str=strtok(phrase," ");
    int flag=3;
    while(1)//EDV APLA GEMIZOYME TOYS PARAPANW PINAKES
    {
        if(str==NULL) break;
        found=binary_search(str,node->children,node->child_num);
        if(found==-1)
        {
            free(temp);
            temp=NULL;
            free(where);
            where=NULL;
            return 0;
        }
        counter++;
        if(counter>size)
        {
            size*=2;
            temp=realloc(temp,size*sizeof(trie_node *));
            where=realloc(where,size*sizeof(int));
        }
        temp[counter-1]=node;
        where[counter-1]=found;
        str=strtok(NULL," ");
        node=node->children[found];
    }
    int i;
    for(i=counter-1;i>=0;i--)//KAI EDV APO THN TELEYTAIA LEKSH TOY N-GRAM KAI PROS TA PISW KSEKINAME THN DIADIKASIA THS DIAGRAFIS
    {
        if(flag==3)//H PRWTH LEKSH POY THA DIAGRAPSOYME
        {
            if(temp[i]->children[where[i]]->is_final=='Y')//AN EINAI TELIKOS KOMVOS
            {
                if(temp[i]->children[where[i]]->child_num==0)//AN DEN EXEI PAIDIA TON DIAGRAFOYME
                {
                    free(temp[i]->children[where[i]]->word);
                    temp[i]->children[where[i]]->word=NULL;
					free(temp[i]->children[where[i]]->children);
					temp[i]->children[where[i]]->children=NULL;
                    free(temp[i]->children[where[i]]);
                    temp[i]->children[where[i]]=NULL;
                    int j;
                    for(j=where[i]+1;j<temp[i]->child_num;j++)
                    {
                        temp[i]->children[j-1]=temp[i]->children[j];
                        temp[i]->children[j]=NULL;
                    }
                    temp[i]->child_num=temp[i]->child_num-1;
                }
                else//AN EXEI APLA TON KANOYME MH TELIKO
                {
                    temp[i]->children[where[i]]->is_final='N';
                    flag--;
                }
            }
            else//AN DEN EINAI TELIKOS LATHOS
            {
                free(temp);
                temp=NULL;
                free(where);
                where=NULL;
                return 0;
            }
            flag--;
        }
        else if(flag==2)//AN DIAGRAPSAME TON KOMVO THS PROHGOYMENHS LEKSHS KOITAME THS EPOMENHS KAI KOITAME NA DOYME AN MPROYME NA TON DIAGRAPSOYME
        {
            if(temp[i]->children[where[i]]->is_final=='N')//AN DEN EINAI TELIKOS KOMVOS
            {
                if(temp[i]->children[where[i]]->child_num==0)//AN DEN EXEI PAIDIA TON DIAGRAFOYME
                {
                    free(temp[i]->children[where[i]]->word);
                    temp[i]->children[where[i]]->word=NULL;
					free(temp[i]->children[where[i]]->children);
					temp[i]->children[where[i]]->children=NULL;
                    free(temp[i]->children[where[i]]);
                    temp[i]->children[where[i]]=NULL;
                    int j;
                    for(j=where[i]+1;j<temp[i]->child_num;j++)
                    {
                        temp[i]->children[j-1]=temp[i]->children[j];
                        temp[i]->children[j]=NULL;
                    }
                    temp[i]->child_num=temp[i]->child_num-1;
                }
                else//AN EXEI DEN KANOYME TIPOTA
                {
                    flag--;
                }
            }
            else
            {
                flag--;
            }
        }
        else
        {
            break;
        }
    }
    if(flag==1)
    {
        free(temp);
        temp=NULL;
        free(where);
        where=NULL;
        return 1;
    }
    else
    {
        free(temp);
        temp=NULL;
        free(where);
        where=NULL;
        return 2;
    }
}
/*int delete_node(trie_node *node,char *phrase)
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
}*/
char* search(Index* indx,char* phrase)
{
	int i,flag=0;
	char *first_word ;
	char *rest_phrase=NULL;
	char** result=malloc(sizeof(char*));		//SE  AUTON TON PINAKA KRATAME TIS LEKSEIS POU THA EMFANISTOUN STO TELOS THS SEARCH//
	int string_counter=-1;						//EINAI O ARITHMOS THESEWN TOU PINAKA RESULT//
	int found=-1;
	char *str2=NULL, *subphrase=NULL;
	char *temp;
	if(phrase==NULL)
	{
		free(result);
		return "-1";
	}
	temp=malloc(strlen(phrase)+1);			//VOITHITIKH METAVLHTH //
	str2=malloc(strlen(phrase)+1);			//VOITHITIKH METAVLHTH //
	strcpy(temp,phrase);
	int str2_flag=0,temp_flag=0;
	while(1)
	{
		if(str2_flag==0 && temp_flag==0)
		{
			first_word=strtok(temp," ");			 //PAIRNOUME THN PRWTH LEKSH THS PHRASHS//
			rest_phrase = strtok(NULL,"");			//PAIRNOUME THN UPOLOIPH PHRASH//
			if(rest_phrase==NULL)
			{
				free(temp);
				free(str2);
				break;
			}
			strcpy(str2,rest_phrase);
			temp_flag=1;
		}
		if(((str2==NULL && str2_flag==0) || (temp==NULL && temp_flag==0)) && flag==1)
		{
			if(temp_flag==1)
			{
				free(temp);
			}
			if(str2_flag==1)
			{
				free(str2);
			}
			break;			//H PHRASH TELEIWSE,EPOMENWS KAI H SEARCH//
		}
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
		}
		flag=1;
		found=-1;
		found=binary_search(first_word,indx->root,indx->root_num);		//PSAXNOUME NA VROUME AN H EPILEGMENH LEKSH VRISKETAI STO ROOT//
		if(found==-1)			//AN DEN UPARXEI STO ROOT SUNEXIZOUME STHN EPOMENH//
		{
			continue;
		}
		else				//AN UPARXEI STO ROOT H PRWTH LEKSH//
		{
			subphrase=malloc(strlen(first_word)+1);    //XRHSIMOPOIOUME MIA VOITHITIKH METAVLHTH POU KRATAME TO APOTELESMA KATHE LEKSHS POU PAIRNOUME APO TO QUESTION//
			strcpy(subphrase,first_word);
			if(indx->root[found]->is_final=='Y')
			{
				int found1=-1;
				for(i=0;i<=string_counter;i++)
				{
					if(!strcmp(result[i],subphrase))		//AN H PHRASH H' LEKSH  POU PROKEITAI NA MPEI STON PINAKA ME TA APOTELESMATA EINAI HDH MESA//
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
			search_node(indx->root[found],rest_phrase,&subphrase,&result,&string_counter);			//AN UPARXEI STO ROOT TOTE ANADROMIKA PHGAINOUME STA PAIDIA//
			free(subphrase);
			subphrase=NULL;
		}
	}
	if(string_counter==-1)		//SE PERIPTWSH POU KAMIA LEKSH DEN VRETHEI EPISTREFOUME -1//
	{
		free(result);
		return "-1";
	}
	char* ready_phrase=malloc(strlen(result[0])+1);		//FTIAXNOUME THN LEKSH POU THA STEILW STHN MAIN GIA NA EKTUPWTHEI//
	strcpy(ready_phrase,result[0]);  					//FTIAXNOUME ENA STRING OPOU THA VALOUME TO TELIKO APOTELESMA POU PROKUPTEI ENWNONTAS OLA TA STRING TOU RESULT//
	for(i=1;i<=string_counter;i++)
	{
		ready_phrase=realloc(ready_phrase,strlen(ready_phrase)+strlen(result[i])+2);
		strcat(ready_phrase,"|");
		strcat(ready_phrase,result[i]);
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
void search_node(trie_node* node,char* phrase,char** subphrase,char*** result,int *length)	//VOITHIKH ANADROMIKH SUNARTHSH POU PSAXNEI MESA STA PAIDIA//
{
	char *str=strtok(phrase," ");
	char* str1=strtok(NULL,"");
	int found=-1,i;
	found=binary_search(str,node->children,node->child_num);
	if(found==-1 )return ;			//AN H PRWTH LEKSH THS PHRASHS POU MAS HRTHE DEN VRETHEI STO TRIE EPISTREFOUME PISW//
	if(found!=-1 && str1==NULL)		//AN VREI THN LEKSH KAI META DEN EXEI ALLH LEKSH EPISHS H ANADROMH TELEIWNEI//
	{
		*subphrase=realloc(*subphrase,strlen(*subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(*subphrase," ");
		strcat(*subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
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
			}
		}
	}
	if(found!=-1 && str1!=NULL)		//AN VREI THN LEKSH KAI META EXEI ALLH LEKSH SUNEXIZOUME STO EPOMENO EPIPEDO THS ANADROMHS MAS//
	{
		*subphrase=realloc(*subphrase,strlen(*subphrase)+strlen(str)+2); //2= " " +/0 //
		strcat(*subphrase," ");
		strcat(*subphrase,str);
		int found1=-1;
		if(node->children[found]->is_final=='Y')
		{
			for(i=0;i<=*length;i++)
			{
				if(!strcmp((*result)[i],*subphrase))		//AN H LEKSH POU PROKEITAI NA MPEI EINAI HDH MESA//
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
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					strcpy(*(result[*length]),*subphrase);

				}
				else				//EXEI MPEI STRING STON PINAKA ARA PREPEI NA KANOUME REALLOC KAI MALLOC//
				{
					(*length)++;
					(*result)=realloc((*result),((*length)+1)*sizeof(char*));
					(*result)[*length]=malloc(strlen(*subphrase)+1);
					strcpy((*result)[*length],*subphrase);
				}
			}
		}
		search_node(node->children[found],str1,subphrase,result,length);		//KALOUME ANADROMIKA THN SUNARTHSH ME TO SWSTO PAIDI POU VRETHIKE//
	}
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
int insertionSort(trie_node** array, int length)
{
   int i, j;
   trie_node* temp;
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
