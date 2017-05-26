/*Seongwoo Choi
scho29
CMPS12B/M
Laboratory Assignment 5
*/

//-----------------------------------------------------------------------------
// Dictionary.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// private types and functions ------------------------------------------------

// NodeObj
typedef struct NodeObj
{
    char *key;
    char *value;
    struct NodeObj *next;

} NodeObj;

// Node
typedef NodeObj *Node;

//Dictionary()
//constructor for the Dictionary Class
typedef struct DictionaryObj
{
    int numPairs;
    Node head;
    Node tail;
    struct NodeObj *next;
}
DictionaryObj;

// newNode()
// constructor for private inner node class
Node newNode(char *k, char *v)
{
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->key = k;
    N->value = v;
    N->next = NULL;
    return (N);
}

// freeNode()
// destructor for private Node type
void freeNode(Node *pNode)
{
    if ( pNode != NULL && *pNode != NULL )
    {
        free(*pNode);
        *pNode = NULL;
    }
}

//findKey()
//returns a reference to the Node at position key in this Dictionary
Node findKey(Node N, char *k)
{
    Node head;
    for (head = N; head != NULL; head = head->next)
    {
        if (strcmp(k, head->key) == 0)
        {
            break;
        }
    }
    return head;
}

// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary()
{
    Dictionary D = malloc(sizeof(DictionaryObj));
    assert(D != NULL);
    D->numPairs = 0;
    return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary *pD)
{
    if ( pD != NULL && *pD != NULL )
    {
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
    }
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D)
{
    if ( D == NULL )
    {
        fprintf(stderr,
                "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return (D->numPairs == 0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D)
{
    if ( D == NULL )
    {
        fprintf(stderr,
                "Dictionary Error: calling size() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return (D->numPairs);
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no
// such value v exists.
// pre: none
char *lookup(Dictionary D, char *k)
{
    Node N = findKey(D->head, k);
    if (N != NULL)
    {
        return N->value;
    }
    else
    {
        return NULL;
    }
    return (N->value);
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char *k, char *v)
{
    Node N;
    if ( D == NULL )
    {
        fprintf(stderr,
                "Dictionary Error: calling insert() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    if ( findKey(D->head, k) != NULL )
    {
        fprintf(stderr,
                "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
        exit(EXIT_FAILURE);
    }
    if (D->numPairs == 0)
    {
        D->head = D->tail = newNode(k, v);
    }
    else
    {
        N = newNode(k, v);
        D->tail->next = N;
        D->tail = N;
    }
    D->numPairs++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char *k)
{
    if ( lookup (D, k) == NULL )
    {
        fprintf(stderr, "Error: calling delete() on non-existent key.\n");
        exit(EXIT_FAILURE);
    }

    if ( findKey(D->head, k) == NULL )
    {
        fprintf(stderr,
                "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
        exit(EXIT_FAILURE);
    }

    Node N;
    Node Q = findKey(D->head, k);

    if (D->numPairs == 1)
    {
        D->head = D->tail = NULL;
        freeNode(&D->head);
    }
    else if (Q == D->head)
    {
        Node z = D->head;
        D->head = D->head->next;
        free(z);
        Q = NULL;
    }
    else if (Q == D->tail)
    {
        N = D->head;
        while (N->next != Q)
        {
            N = N->next;
        }
        N->next = NULL;
        D->tail = N;
    }
    else
    {
        N = D->head;
        while (N->next != Q)
        {
            N = N->next;
        }
        N->next = Q->next;
    }
    free(Q);
    D->numPairs--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D)
{
    Node N;
    while ( D->numPairs > 0)
    {
        N = D->head;
        D->head = (D->head)->next;
        freeNode(&N);
        D->numPairs--;
    }
}
// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE *out, Dictionary D)
{
    Node N;
    if ( D == NULL )
    {
        fprintf(stderr,
                "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    for (N = D->head; N != NULL; N = N->next) fprintf(out, "%s %s \n", N->key, N->value );
}