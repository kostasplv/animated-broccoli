#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"
#include "ngrams.h"
#include <stdlib.h>


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{

   return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{

   return 0;
}

void testSearch(void)
{
	Index *Trie;
	Trie=init_trie();
	char *phrase=malloc(100*sizeof(char));
		char* temp=search(Trie,"");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie," ");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"-1"));
		strcpy(phrase,"this");
		insert_ngram(Trie,phrase);
		temp=search(Trie,phrase);
		CU_ASSERT(0==strcmp(temp,phrase));
	   	free(temp);
		strcpy(phrase,"this is a ball");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"is this");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"ball");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"this is");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"this is a ball");
		CU_ASSERT(0==strcmp(temp,"this|this is a ball"));
	   	free(temp);
		strcpy(phrase,"this is a dog");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"this is");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"ball dog");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"is this");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"this is a dog");
		CU_ASSERT(0==strcmp(temp,"this|this is a dog"));
	   	free(temp);
		temp=search(Trie,"this is a ball and this is a dog");
		CU_ASSERT(0==strcmp(temp,"this|this is a ball|this is a dog"));
	   	free(temp);
		strcpy(phrase,"is a dog and");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"this"));
	   	free(temp);
		temp=search(Trie,"is");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"is a dog");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"is a dog and");
		CU_ASSERT(0==strcmp(temp,"is a dog and"));
	   	free(temp);
		temp=search(Trie,"this is a dog and");
		CU_ASSERT(0==strcmp(temp,"this|this is a dog|is a dog and"));
	   	free(temp);
		strcpy(phrase,"is");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"is");
		CU_ASSERT(0==strcmp(temp,"is"));
	   	free(temp);
		strcpy(phrase,"is a dog");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"is a");
		CU_ASSERT(0==strcmp(temp,"is"));
	   	free(temp);
		temp=search(Trie,"this is a dog and this is a ball");
		CU_ASSERT(0==strcmp(temp,"this|this is a dog|is|is a dog|is a dog and|this is a ball"));
	   	free(temp);
	   	strcpy(phrase,"a");
	   	insert_ngram(Trie,phrase);
	   	temp=search(Trie,"is a");
	   	CU_ASSERT(0==strcmp(temp,"is|a"));
	   	free(temp);
	   	temp=search(Trie,"a");
	   	CU_ASSERT(0==strcmp(temp,"a"));
	   	free(temp);
	   	temp=search(Trie,"this is a this is a");
	   	CU_ASSERT(0==strcmp(temp,"this|is|a"));
	   	free(temp);
   free(phrase);
   delete_trie(&Trie);
}

void testInsert(void)
{
	Index *Trie;
	Trie=init_trie();
	char *phrase=malloc(100*sizeof(char));
		char* temp=search(Trie,"");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie," ");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"this dsad ads");
		CU_ASSERT(0==strcmp(temp,"-1"));
		strcpy(phrase,"this");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"this"));
		free(temp);
		strcpy(phrase,"this is");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this is");
		CU_ASSERT(0==strcmp(temp,"this|this is"));
		free(temp);
		strcpy(phrase,"this is a dog");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this is a dog");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a dog"));
		free(temp);
		temp=search(Trie,"this is a cat");
		CU_ASSERT(0==strcmp(temp,"this|this is"));
		free(temp);
		strcpy(phrase,"this is a cat");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"this is a cat");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a cat"));
		free(temp);
		temp=search(Trie,"is");
		CU_ASSERT(0==strcmp(temp,"-1"));
		strcpy(phrase,"is");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"is");
		CU_ASSERT(0==strcmp(temp,"is"));
		free(temp);
		temp=search(Trie,"is a cat");
		CU_ASSERT(0==strcmp(temp,"is"));
		free(temp);
		strcpy(phrase,"is a cat");
		insert_ngram(Trie,phrase);
		temp=search(Trie,"is a cat");
		CU_ASSERT(0==strcmp(temp,"is|is a cat"));
		free(temp);
	free(phrase);
	delete_trie(&Trie);
}
void testBinary(void)
{
	Index* Trie;
	Trie=init_trie();
	char *phrase=malloc(100*sizeof(char));
      CU_ASSERT(-1 == binary_search("",Trie->root,Trie->root_num));
      strcpy(phrase,"this");
      insert_ngram(Trie,phrase);
      CU_ASSERT(-1 != binary_search("this",Trie->root,Trie->root_num));
      strcpy(phrase,"is");
      insert_ngram(Trie,phrase);
      CU_ASSERT(-1 != binary_search("is",Trie->root,Trie->root_num));
      CU_ASSERT(-1 == binary_search("thiss",Trie->root,Trie->root_num));
      strcpy(phrase,"a");
      insert_ngram(Trie,phrase);
      CU_ASSERT(-1 != binary_search("is",Trie->root,Trie->root_num));
      CU_ASSERT(-1 != binary_search("this",Trie->root,Trie->root_num));
      CU_ASSERT(-1 != binary_search("a",Trie->root,Trie->root_num));
      CU_ASSERT(-1 == binary_search("this is a",Trie->root,Trie->root_num));
   free(phrase);
   delete_trie(&Trie);
}
int test(trie_node** node,int length)
{
	int i;
	for(i=0;i<length-1;i++)
	{
		if(strcmp(node[i]->word,node[i+1]->word)>0)
		{
			return 0;
		}
	}
	return 1;
}
void testInsertion(void)
{
	Index* Trie;
	Trie=init_trie();
	char* phrase=malloc(100*sizeof(char));
	int i;
      strcpy(phrase,"this");
      insert_ngram(Trie,phrase);
      CU_ASSERT(1 == test(Trie->root,Trie->root_num));

      strcpy(phrase,"a");
      insert_ngram(Trie,phrase);
      CU_ASSERT(1== test(Trie->root,Trie->root_num));

      strcpy(phrase,"c");
      insert_ngram(Trie,phrase);
      CU_ASSERT(1 == test(Trie->root,Trie->root_num));

      strcpy(phrase,"thit");
      insert_ngram(Trie,phrase);
   free(phrase);
   delete_trie(&Trie);
}

void testDelete(void)
{
    Index *Trie;
    Trie=init_trie();
    char *phrase=malloc(100*sizeof(char));
    char *testit=malloc(100*sizeof(char));
    char *temp;
		temp=search(Trie,"");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie," ");
		CU_ASSERT(0==strcmp(temp,"-1"));
		temp=search(Trie,"this dsad ads");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(phrase,"this is a cat and a dog and a mouse");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat and a dog and a");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat and a dog and");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat and a dog");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat and a");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat and");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a cat");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is a");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this is");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"this");
        insert_ngram(Trie,phrase);
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"this"));
		free(temp);
        temp=search(Trie,"this is");
		CU_ASSERT(0==strcmp(temp,"this|this is"));
		free(temp);
		temp=search(Trie,"this is a");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a"));
		free(temp);
		temp=search(Trie,"this is a cat");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat"));
		free(temp);
		temp=search(Trie,"this is a cat and");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and"));
		free(temp);
		temp=search(Trie,"this is a cat and a");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and|this is a cat and a"));
		free(temp);
		temp=search(Trie,"this is a cat and a dog");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog"));
		free(temp);
		temp=search(Trie,"this is a cat and a dog and");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and"));
		free(temp);
		temp=search(Trie,"this is a cat and a dog and a");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a"));
		free(temp);
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this|this is|this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
        strcpy(testit,"this");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is|this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this");
		CU_ASSERT(0==strcmp(temp,"-1"));

        strcpy(testit,"this is");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a|this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat|this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and|this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and a|this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and a");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and a dog|this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and a dog");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and a dog and|this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and a dog and");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and a dog and a|this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and a dog and a");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"this is a cat and a dog and a mouse"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a");
		CU_ASSERT(0==strcmp(temp,"-1"));
        strcpy(testit,"this is a cat and a dog and a mouse");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"-1"));
		CU_ASSERT(0==delete_ngram(Trie,testit));
		temp=search(Trie,"this is a cat and a dog and a mouse");
		CU_ASSERT(0==strcmp(temp,"-1"));

        strcpy(phrase,"league of legends world championship");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"league of legends");
        insert_ngram(Trie,phrase);
		temp=search(Trie,"league of legends world championship");
		CU_ASSERT(0==strcmp(temp,"league of legends|league of legends world championship"));
		free(temp);
        strcpy(testit,"league of legends world championship");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"league of legends world championship");
		CU_ASSERT(0==strcmp(temp,"league of legends"));
		free(temp);
		CU_ASSERT(0==delete_ngram(Trie,testit));
        strcpy(phrase,"overwatch pro league");
        insert_ngram(Trie,phrase);
        strcpy(phrase,"overwatch");
        insert_ngram(Trie,phrase);
        temp=search(Trie,"league of legends");
        CU_ASSERT(0==strcmp(temp,"league of legends"));
        free(temp);
        temp=search(Trie,"overwatch");
        CU_ASSERT(0==strcmp(temp,"overwatch"));
        free(temp);
        temp=search(Trie,"overwatch pro league");
        CU_ASSERT(0==strcmp(temp,"overwatch|overwatch pro league"));
        free(temp);
        strcpy(testit,"overwatch pro league");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"overwatch pro league");
		CU_ASSERT(0==strcmp(temp,"overwatch"));
		free(temp);
        strcpy(testit,"overwatch");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"overwatch");
		CU_ASSERT(0==strcmp(temp,"-1"));
        temp=search(Trie,"league of legends");
        CU_ASSERT(0==strcmp(temp,"league of legends"));
        free(temp);
        strcpy(testit,"league of legends");
        CU_ASSERT(1==delete_ngram(Trie,testit));
		temp=search(Trie,"league of legends");
		CU_ASSERT(0==strcmp(temp,"-1"));
    free(testit);
    free(phrase);
    delete_trie(&Trie);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of Search()", testSearch))
		   ||(NULL == CU_add_test(pSuite, "test of delete()", testDelete))
		   ||(NULL == CU_add_test(pSuite, "test of Insert()", testInsert))
		   ||(NULL == CU_add_test(pSuite, "test of Binary()", testBinary))
		   ||(NULL == CU_add_test(pSuite, "test of InsertionSort()", testInsertion)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
