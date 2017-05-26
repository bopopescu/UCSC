//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
// Programming Assignment 2
// Professor Tantalo
// CMPS 101 
// Seongwoo Choi
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "List.h"

int main(int argc, char* argv[]){

	int i;
	List A = newList();
	List B = newList();

	for (i=0; i< 10; i++) {
		append(A,i);
		prepend(B,i);
	}

	//this section is a method of traversing the list.
	for (moveFront(A,length(A)-1); index(A)!=-1; movePrev(A)) {
		//fprintf(stdout, "%d ", getElement(A));
		fprintf(stdout, "%d ", get(A));
	}
	printf("\n");

	for (int i = 0; i < length(A); i++) {
		moveFront(A, i);
		fprintf(stdout, "%d ", get(A));
	}
	printf("\n");

	int insert = 69;

	printList(stdout, A);
	moveFront(A,0);
	insertBefore(A, insert);
	printList(stdout, A);
	moveFront(A, length(A)-1);
	insertBefore(A, insert);
	printList(stdout, A);
	moveFront(A, 6);
	insertBefore(A, insert);
	printList(stdout, A);

	insert = 11;
	printf("\n");
	printList(stdout, B);
	moveFront(B,0);
	insertAfter(B, insert);
	printList(stdout, B);
	moveFront(B, length(B)-1);
	insertAfter(B, insert);
	printList(stdout, B);
	moveFront(B, 6);
	insertAfter(B, insert);
	printList(stdout, B);
	
	printf("\n");

	printList(stdout, A);
	printList(stdout, B);
	
	int loopBound = length(A);
	for (int i = 0; i < loopBound;i++) deleteFront(A);
	printList(stdout, A);

	//freeList(&A);
	//freeList(&B);

	return(0);
}
