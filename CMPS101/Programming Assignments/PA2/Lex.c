/*
* Seongwoo Choi	
* CMPS 101
* Summer 2015
* Programming Assignment 2
* Lex.c
* Patrick Tantalo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160
typedef char *string;

int main (int argc, char* argv[]) {
	// This area checks for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit (1);
	}
	// Initiate Variables
	FILE *in, *in1, *out;
	char line[MAX_LEN];
	char lineCounter[MAX_LEN];
	int numlines = 0;
	int count =0, i,j,cmp;
	
	// Opening Files
	in1 = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in1 == NULL) {
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	} if (out == NULL) {
		printf("Unable to open file %s for writing.\n", argv[2]);
		exit(1);
	}
	// this while loop counts the number of input lines
	while (fgets(lineCounter, MAX_LEN, in1) != NULL) {
		numlines++;
		//printf("%s\n", lineCounter);
	}
	string lineArray[numlines];
	// fclose() and fopen(). Closes the file buffer and reopen it
	fclose(in1);
	in = fopen(argv[1], "r");
	if (in1 == NULL) {
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	}
	// In here, the code populatse the string array with the lines from the input file.
	while (fgets(line, MAX_LEN, in) != NULL) {
		i = strlen(line) + 1;
		lineArray[count] = malloc(sizeof(char)*i);
		strcpy(lineArray[count],line);
		count++;
	}

	// Go through the array of lines and insert in lex. order
	List lineList = newList();
	append(lineList,0);
	// Go through the array
	for (j=1; j < numlines; j++) {
		// Select the appropriate position in the list
		moveFront(lineList, 0);
		for (i=0; i<length(lineList);i++) {
			moveFront(lineList,i);
			string temp = lineArray[get(lineList)];
			cmp = strcmp(lineArray[j],temp);
			// Insert before if lex. less than
			if (cmp < 0) {
				insertBefore(lineList, j);
				break;
			// If reached the end of the list, append
			} else if (i == length(lineList)-1) {
				append(lineList,j);
				break;
			}
		}
	}
	// Print from the List
	//printf("Printing from List: \n");
	for (moveFront(lineList, 0); index(lineList)!=-1; moveNext(lineList)) {
		fprintf(out,"%s", lineArray[get(lineList)]);
	}
	// Print from the Array
	//printf("Printing from Array: \n");
	//for (j=0; j < numlines; j++) printf("%s", lineArray[j]);

	// Clean up:
	// Frees up the malloc'd space for the line Array
	for (j=0; j< numlines; j++) {free(lineArray[j]);}
	// Frees the list
	freeList(&lineList);
	// Closes all the opened files
	fclose(in);
	fclose(out);
	return(0);
}
