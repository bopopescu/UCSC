/*
CMPS 111 
Winter 2017
Assignment 2
Erik Andersen (Team Captain)
Seongwoo Choi
Yuzhuang Chen
Michael Cardoza
write_test.c
*/

/*
Libraries
*/
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
The main function will open input file and then read over the arguments and then write on 
an output file. 
*/
int main (int argc, char* argv[]) {
	char buffer[20];
	int file_in = open(argv[1], O_RDONLY);
	int file_out = open(argv[2], O_WRONLY | O_CREAT, 0644);
	size_t nbytes;
	size_t rd_bytes;
	nbytes = sizeof(buffer);

	if (file_in < 0 ) {
		perror("there is an error");
	} else (file_in >= 0);
		while ( (rd_bytes = read(file_in, buffer, nbytes)) > 0) {
			write(file_out, buffer, rd_bytes);
	}
	close(file_in);
	close(file_out);
	return 0;
}

