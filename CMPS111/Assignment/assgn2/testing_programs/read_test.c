/*
CMPS 111 
Winter 2017
Assignment 2
Erik Andersen (Team Captain)
Seongwoo Choi
Yuzhuang Chen
Michael Cardoza
read_test.c
*/

/*
Libraries
*/
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/*
Variables
*/
int i;
int process;
int status;
int maximum; 
int children;
pid_t pid, cpid;

int gift() {
    for (i =0; i < 10; i++) {
    while (status < maximum) {
            ++status;
            if ((status % 100000) == 0 || (maximum - status) < 10){
                printf("%d gift Process: %d", getpid(), (maximum-status));
                }
            }
        }        
    }

/*
Main function goes down the pipe of child process
Similar to the second lab assignment. 
*/
int main(int argc, char *argv[]) {
	int i;

/*Convert string to integer
Parses the C-string str interpreting its content as an integral number, which is returned as a value of type int.

The function first discards as many whitespace characters (as in isspace) as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many base-10 digits as possible, and interprets them as a numerical value.
*/
    maximum = atoi (argv[1]);
    status = 0;
    children = 0;

    for (i =0; i < 10; i++) {
    	switch(pid = fork()) {
    		case 0: 
    		printf("Child fork %d PID: %d\n", children, getpid());
    		++children;
    		status = 0; 
    		while (status < maximum) {
    			++status;
    			if ((status % 100000) == 0 || (maximum - status) < 10){
    					printf("%d Child Process: %d, %12d needs to process\n", getpid(), (maximum-status));
    				}
    			}
    		break;

    		case -1:
    		printf("Child fork does not work here");
    		perror("fork");
    		exit(1);

    		default :
        	printf("Parent Process ID: %d\n", getpid());
            while(status < maximum){
               ++status;
               if (status % 1000 == 0 || (maximum - status) < 10){
                   printf("%d Parent PID: %d, %12d to go\n", children, getpid(), (maximum - status));
               }
            }
            break;
        }
	while((pid = wait(&process)) != -1) {
		gift();
		printf("End of Process\n");
		return 0;            

    			}
    		}
    	}

