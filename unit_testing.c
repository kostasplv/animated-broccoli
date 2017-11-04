#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"
#include "ngrams.h"
#include <stdlib.h>

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testInsert(void)
{
	Index *Trie;
	Trie=init_trie();
	char *phrase=malloc(100*sizeof(char));
   if (NULL != temp_file)
   {
	   CU_ASSERT(0==strcmp(search(Trie,""),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie," "),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie,"this"),"-1"));
	   strcpy(phrase,"this");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,phrase),phrase));
	   strcpy(phrase,"this is a ball");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"this"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"is this"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"ball"),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a ball"),"this|this is a ball"));
	   strcpy(phrase,"this is a dog");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"this"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"ball dog"),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie,"is this"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a dog"),"this|this is a dog"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a ball and this is a dog"),"this|this is a ball|this is a dog"));
	   strcpy(phrase,"is a dog and");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"this"),"this"));
	   CU_ASSERT(0==strcmp(search(Trie,"is"),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie,"is a dog"),"-1"));
	   CU_ASSERT(0==strcmp(search(Trie,"is a dog and"),"is a dog and"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a dog and"),"this|this is a dog|is a dog and"));
	   strcpy(phrase,"is");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"is"),"is"));
	   strcpy(phrase,"is a dog");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"is a"),"is"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a dog and this is a ball"),"this|this is a dog|is|is a dog|is a dog and|this is a ball"));
	   strcpy(phrase,"a");
	   insert_ngram(Trie,phrase);
	   CU_ASSERT(0==strcmp(search(Trie,"is a"),"is|a"));
	   CU_ASSERT(0==strcmp(search(Trie,"a"),"a"));
	   CU_ASSERT(0==strcmp(search(Trie,"this is a this is a"),"this|is|a"));
   }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testDelete(void)
{
   unsigned char buffer[20];

   if (NULL != temp_file)
   {
      rewind(temp_file);
      //YOUR CODE HERE//
      CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));		//SVISTA AUTA//
      CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));							//SVISTA AUTA//
      //YOUR CODE HERE//
   }
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
   if ((NULL == CU_add_test(pSuite, "test of Insert()", testInsert)) ||(NULL == CU_add_test(pSuite, "test of delete()", testDelete)))
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

