
#include "./str.h"

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

