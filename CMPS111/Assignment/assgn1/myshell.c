/*
	Seongwoo Choi
	scho29
	CMPS 111
	Winter 2017
    Darrell Long 
	1368039
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>

extern char **getline();
extern int MAX_ARGS;
int i;
int current_status;
int s;
int inside_file;
int outside_file;
int fd_pipe[2];
pid_t pid, cpid;
int error;
char **savedargs = NULL;
int saved_pid = 0;
int check_background(char** arglist);

#define TRUE 1
#define FALSE 0

// prints an error message. 
void print_error (char *string) {
	error = TRUE;
	fprintf (stderr, "the shell: %s\n", string);
}

/*
This is the main function of the program. The shell prints a message
to the user and then execute what the user is asking it to do. 
*/
int main() {
    char **args;
    printf("Welcome to myShell! \n Made by Seongwoo Choi\n");
    while(1) {        
        printf("SWC's shell$: ");  

        args = getline();

        switch(pid = fork()) {
        // Error Code when there is an error
        case -1:
            perror("fork error occurred");
            exit(1);

        // Child Code
        case 0: 
            s = special_cmd(args);
        // Parent Code
        default :
            while ((pid = wait(&current_status)) != -1){ }
            if(args[0] == NULL){ }
            else if (strcmp(args[0], "exit") == 0) { exit(0); }
        }
    } 
}

int check_background(char** arglist){
    int i;
    for(i = 0 ; arglist[i] != NULL ; i++){
        if(strcmp(arglist[i] , "&") == 0){
            return 1;
        }
    }
    return 0;
}


// A command with arguments
// The shell blocks until the command completes and, if 
// the retun code is abnormal, print out a message detailing the 
// error. This holds for all command strings in this assignment.
// special_cmd goes through the piping procedure and special argument
// this determines if the user added any special command on the terminal
int special_cmd(char *args[]) {
	if(args[0] == NULL) { exit(0); } else {
		for(i = 0; args[i] != NULL; i++) {
			switch(*args[i]) {
			case '>' : outside_file = open(args[i+1], O_WRONLY | O_CREAT, 0644);
            if(outside_file == -1){
                perror("open");
                exit(1);                
            }
            if(dup2(outside_file, 1) == -1){
                perror("dup2");
                exit(1);
            }
            args[i++] = NULL;
            args[i] = " ";
            break;

            /* This part of the program redirect output 
                to the file after "<" . A command, with or without 
                arguments, whose output is redirected to a file. 
            */
            case '<' : inside_file = open(args[i+1], O_RDONLY);
            if(inside_file == -1){
                perror("open");
                exit(1);                
            }
            if(dup2(inside_file, 0) == -1){
                perror("dup2");
                exit(1);
            }
            args[i++] = NULL;
            args[i] = " ";
            break;

            /*
            When a user entered '&', then initiate this
            */
            case '&' : inside_file = open(args[i+1], SIGCHLD);
            if(inside_file == 0){
                perror("open");
                exit(1);
            }
            if(wait4(int *inside_file, int *current_status, struct rusage *rusage, int options) == -1){
                perror("wait");
                exit(1);
            }
            args[i++] = NULL;
            args[i] = " ";
            break;

            case '|' : 
            // This area of the code opens a pipe between two processes
            // this is a piping procedure. 
            pipe(fd_pipe);
            switch(cpid = fork()){
            // Error Code
            case -1 :
                perror("fork");
                exit(1);

            // Child Code
            case 0 :
                dup2(fd_pipe[1], 1);
                close(fd_pipe[0]);
                while (i < MAX_ARGS){
                    args[i++] = NULL;
                }
                break;

            // This is a Parent Code
            default :
                dup2(fd_pipe[0], 0);
                close(fd_pipe[1]);
                while ((pid = wait(&current_status)) != -1){ }

                args[i++] = NULL;
                for (int j = 0; j+i < MAX_ARGS; ++j){
                    args[j] = args[i+j];
                }
                if (args[0] != NULL){
                    s = special_cmd(args);
                }
            } 
            break;

        default :
            if (strcmp(args[0], "exit") == 0) { exit(0); }
            break;
        }
        } }
    if(args[0] == NULL){ }
    else if(execvp(args[0], args) == -1){
       perror(args[0]);
       exit(1);
    }
    return 0;
}


