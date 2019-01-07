#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

/* 
 * this functions returns first coming into the string 
 * or -1 if don't find it.
*/
int chrInStr(const char c, const char *str){
	char *pstr = str;
	while(*pstr){
		if(*pstr++ == c){
			return pstr-str;
		}
	}
	return -1;
}

/*
 *Writes into buff a string of an ip address
 *which is a num.
*/
char *int2ip(const char *buff, uint32_t num){
	char *pbuff = buff;
	for(int i=0; i<4 ; ++i){
		itoa(pbuff, *(((char *)&num)+i) );
		pbuff += strlen(buff);
		*pbuff++ = '.';
	}
	return buff;
}

int main(int argc, char **argv){
	char buf[1024];

	printf(  "%s\n", iint2ip( buf, atoi(argv[1]) )  );

	/* exit */
	return 0;
}
