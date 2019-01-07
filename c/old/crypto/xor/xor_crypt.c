#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

char *xor_crypt(char *dst, char *str, char *key){
	char *startdst = dst;
	uint64_t keylen = strlen(key);

	while(*str){
		*dst = *str ^ key[ (dst-startdst) % keylen];
		++dst, ++str;
	}

	*dst = '\0';

	return startdst;
}

int main(int argc, char **argv){
	char buf[1024];
	printf("%s", xor_crypt(buf, argv[1], argv[2]) );
	/* Default exit. */
	return 0;
}
