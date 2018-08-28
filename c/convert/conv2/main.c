#include <stdio.h>
#include <stdlib.h>

#define PROG_NAME "conv2"

int main(int argc, char **argv){
	if( argc<4 ){
		fprintf(stderr, "%s: Not enough arguments.\n", PROG_NAME);
		exit(1);
	}

	/* Successful exit. */
	return 0 ;
}
