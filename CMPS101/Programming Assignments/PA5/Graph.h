/* Seongwoo Choi
* scho29@ucsc.edu
* CMPS101: Introduction to Algorithms
* Patrick Tantalo
* Summer 2015
*/

#include "List.h"

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0

// Graph Type
typedef struct  GraphObj* Graph;

// Constructors and Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation Procedures
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

// Other
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif