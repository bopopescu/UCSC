/*
 *Seongwoo Choi
 *scho29
 *CMPS12B/M
 *Programming Assignment 5
 *This program creates a Dictionary ADT by hashing with the function
 *(int)k mode (100)tableSize;
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "Dictionary.h"


const int tableSize=101;
/* creates the node data type*/
typedef struct NodeObj{
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;
/* Dictionary
 Printed out reference type
 */
typedef NodeObj* Node;

/*Constructor for the node data type*/
Node newNodeObj(char* k, char* v){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = k;
	N->value = v;
	N->next = NULL;
	return(N);
}
/*Free's the heap memory for the node data type*/
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}
/* this creates the list data type*/
typedef struct List{
	Node front;
	int size;
}List;
typedef List* ListRef;
/*this is a constructor for the node data type*/
ListRef newList(void){
	ListRef L = malloc(sizeof(List));
	assert(L!=NULL);
	L->front = NULL;
	L->size = 0;
	return L;
}
/*free the heap memory from list*/
void freeList(ListRef* pL){
	free(*pL);
	*pL = NULL;
}
/*creates the Dictionary data type*/
typedef struct DictionaryObj{
	ListRef* table;
	int numItems;
}DictionaryObj;
/*Given Functions*/
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if ( shift == 0 )
		return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
 }
 return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
 return pre_hash(key)%tableSize;
}


/* newDictionary()
constructor for the Dictionary type
*/
Dictionary newDictionary(void){
	int i;
	Dictionary D = malloc(sizeof(DictionaryObj)); /*added obj */
	assert(D!=NULL);
	D->table = calloc(tableSize+1, sizeof(NodeObj)); /*LisRef to NodeObj*/
	D->numItems = 0;
	for(i=0; i<tableSize; i++){
		D->table[i] = newList();
	
	}
	return D;	
}
/* freeDictionary()
 destructor for the Dictionary type
 */
void freeDictionary(Dictionary* pD){
		free(*pD);
		*pD = NULL;
}
/* isEmpty()
 returns 1 (true) if S is empty, 0 (false) otherwise
pre: none
*/
int isEmpty(Dictionary D){
	if( D == NULL){
		fprintf(stderr,"Stack Error: calling isEmpty() on NULL StackRef\n");
		exit(EXIT_FAILURE);
	}
	return(D->numItems==0);
}
/* size()
 returns the number of (key, value) pairs in D
 pre: none
 */
int size(Dictionary D){
	if(D == NULL){
		fprintf(stderr,"Stack Error: calling size() on NULL Dictionary\n");
		exit(EXIT_FAILURE);
	}
	return(D->numItems);
}
/* lookup()
 returns the value v such that (k, v) is in D, or returns NULL if no 
 such value v exists.
 pre: none
 */
char* lookup(Dictionary D, char* k){
	Node N=D->table[hash(k)]->front;
	while(N != NULL){
		if(N->key == k){ /*strcmp?? */
			return N->value;
		}
		N = N->next;
	}
	return NULL; /*NULL? */
}
/* insert()
   inserts new (key,value) pair into D
 pre: lookup(D, k)==NULL
 */
void insert(Dictionary D, char* k, char* v){
	int h = hash(k);
	Node N = newNodeObj(k,v);
	if(D==NULL){
		fprintf(stderr, "Stack Error: calling insert() on NULL StackRef\n");
		exit(EXIT_FAILURE);
	 }
	if(lookup(D,k)!=NULL){ 
		fprintf(stderr, "Stack Error: inserting dublicate key\n");
		exit(EXIT_FAILURE);
	}
	if(D->table[h]->front == NULL){
		D->table[h]->front = N;
		D->numItems++;
	}
	else{
		N->next = D->table[h]->front;
		D->table[h]->front = N;
	}
}
 /* delete()
 deletes pair with the key k
 pre: lookup(D, k)!=NULL
 */
void delete(Dictionary D, char* k){
	int h = hash(k);
	Node N = D->table[h]->front;
	Node P = NULL;
	if(D==NULL){
		fprintf(stderr, "Stack Error: calling delete() on NULL Dictionary\n");
		exit(EXIT_FAILURE);
	}
	if(lookup(D,k)==NULL){ 
		fprintf(stderr, "Stack Error: deleting non-existant key\n");
		exit(EXIT_FAILURE);
	}
	if( D->table[h]->size == 1){
		freeNode(&N);
	}
	else if (N->key == k){
		P = N;
		D->table[h]->front = N->next;
		freeNode(&P);
	}
	else{
		while(N->next->key != k){
			N = N->next;
		}
		P = N->next;
		N->next = P->next;
		freeNode(&P);
	}
	D->numItems--;
	D->table[h]->size--;
}

/* makeEmpty()
 re-sets D to the empty state.
 */
void makeEmpty(Dictionary D){
	if( D == NULL){
		fprintf(stderr,"Stack Error: calling makeEmpty() on NULL DictionaryRef\n");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i=0; i<tableSize; i++){
		D->table[i]->size = 0; 
		freeNode(&D->table[i]->front);		
	}
	D->numItems = 0;
}
/* printDictionary()
 // this prints a text representation of D to the file pointed to by out
 */
void printDictionary(FILE* out, Dictionary D){	/*printDictionary */
	if( D == NULL){
		fprintf(stderr,"Stack Error: calling printDictionary() on NULL DictionaryRef\n");
		exit(EXIT_FAILURE);
	}
	Node N = NULL;
	int i;
	for( i=0; i<tableSize; i++){
		N = D->table[i]->front;
		while( N!=NULL){
			fprintf(out,"%s %s\n",N->key,N->value);
			N = N->next;
		}
	}
}


