#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../str.h"

char *strrev(char *dest, char *str){
	char *pbuf = malloc( sizeof(char) * strlen(str) );
	char *pbufstart = pbuf;
	uint64_t len = 0;

	while(*str){
		++str, ++len;
	}

	/* to escape zero end character */
	--str;
	for( ; len ; --len){
		*pbuf++ = *str--;
	}

	*pbuf = '\0';
	strcpy(dest, pbufstart);

	free(pbufstart);


	return dest;
}

/*
int main(int argc, char **argv){
	char buf[BUFSIZE];
	if(argc<2){
		printf("%s: too few arguments\n", argv[0]);
		return 1;
	}

	printf("'%s'", strrev(buf, argv[1]));

	//default exit
	//
	return 0;
}
*/

