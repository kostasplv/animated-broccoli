#ifndef NGRAMS_H_
#define NGRAMS_H_
typedef struct Index Index;
typedef struct trie_node trie_node;
struct trie_node
{
	char* word;
	trie_node** children;
	char is_final;
	int child_num;
	int node_size;
};
struct Index
{
	trie_node** root;
	int root_size;
	int root_num;
};
int insertionSort(trie_node** arr, int length);
Index* init_trie();
trie_node* create_trie_node();
int insert_ngram(Index*,char*);
int delete_ngram(Index*,char *);
int delete_node(trie_node *,char *);
void insert_node(trie_node* node,char* phrase);
char* search(Index*,char*);
void search_node(trie_node* node,char* phrase,char**,char***,int*);
void delete_trie(Index **);
void delete_helper(trie_node *);
int binary_search(char* phrase,trie_node** node,int length);
#endif /* NGRAMS_H_ */
