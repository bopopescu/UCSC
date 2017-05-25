/*
   Seongwoo Choi
   scho29
   Winter 2017
   assgn0
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	int i;
	int content;
	int vb;
	int count;
	char swc[1024];
  
	if (argc == 1) // is there a file in the argument?
	{
    	     while(1){
		vb = read(STDIN_FILENO, swc, sizeof(swc));
		if(vb<0) { // if there is no file there
			perror ("Error reading from STDIN");
			return -1; // exit the program
		} else if (vb == 0){ // if it is zero
			return 0;
		} else { // if it is something else then execute this:
			count = write (STDOUT_FILENO, swc, vb);
			if (count != vb) {
				perror ("Error writing in STDOUT");
				return -1;
			}
		}
	     }
	}
	else // if there are more than one argument, then...
	{
    		for (i = 1; i < argc; i++)
    		{
        		content = open (argv[i], O_RDONLY);
        		if (content <= 0){
            			perror("Error: Cannot open :(");
				return -1;
        		}else
        		{
            			while (1) {
			                vb= read (content, swc, sizeof(swc));
                			if (vb < 0) {
                        			perror ("Reading Error from file") ;
                        			return -1;
                			} else if (vb == 0){
						break;
					} else {
                        			count = write (STDOUT_FILENO, swc, vb);
                        			if (count != vb) {
                                			perror ("Error writing in STDOUT");
                                			return -1;
                        			}
                			}
             			}
        		}
			if (close(content) == -1) { // if you cannot close files, 
                		perror ("Error in closing files");
            		}
    		}
	}
	return 0;
}
