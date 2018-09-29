/* This program converts data from on to another one view. */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define PROG_NAME "conv2"

uint32_t ipv4_2_bin(char *ip){
}

char *bin_2_ipv4(char *dst, uint32_t bin){
}


uint64_t ipv6_2_bin(char *ip){
}

char *bin_2_ipv6(char *dst, uint64_t bin){
}


int main(int argc, char **argv){
	if( argc<4 ){
		fprintf(stderr, "%s: Not enough arguments.\n", PROG_NAME);
		exit(1);
	}



	/* Successful exit. */
	return 0 ;
}
