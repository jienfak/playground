#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../../str/str.h"

char *itoa(char *dest, int num){
	char *pbuf = dest;
	char *pbufstart = pbuf;

	/* for minus sign */
	if(num<0){
		*pbuf++ = '-';
	}

	char *torev = pbuf;
	while(num){
		*pbuf++ = num%10;
		num /= 10;
	}

	strrev(torev, torev);

	return pbufstart;
}

int main(int argc, char **argv){
	char buf[1024];
	printf("'%s' = %d\n", itoa(buf, 123), 123);

	/* default exit */
	return 0;
}
