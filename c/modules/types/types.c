#include "../../str/str.h"
#include "./types.h"

/* converting from 'int' to 'str'(ZERO-end string) */
char *itoa(char *dest, int num){
	char *pbuf = dest ;
	char *pbufstart = pbuf ;

	if(num == 0){
		*pbuf++ = '0' ;
		*pbuf = '\0' ;
		return pbufstart ;
	}

	/* for minus sign */
	if(num<0){
		*pbuf++ = '-' ;
		num = -num ;
	}

	/* place to reverse a string */
	char *torev = pbuf ;
	while(num){
		*pbuf++ = (num%10) + '0' ;
		num /= 10 ;
	}

	strrev(torev, torev);
	*pbuf = '\0' ;

	return pbufstart ;
}
