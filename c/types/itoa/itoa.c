#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#include "../../str/str.h"

char *itoa(char *dest, int num){
	char *pbuf = dest;
	char *pbufstart = pbuf;

	if(num == 0){
		*pbuf++ = '0';
		*pbuf = '\0';
		return pbufstart;
	}

	/* for minus sign */
	if(num<0){
		*pbuf++ = '-';
		num = -num;
	}

	char *torev = pbuf;
	while(num){
		*pbuf++ = (num%10) + '0';
		num /= 10;
	}

	strrev(torev, torev);
	*pbuf='\0';

	return pbufstart;
}

int main(int argc, char **argv){
	char buf[1024];
	int num = -256;
	printf("'%s' = %d\n", itoa(buf, num), num);

	/* default exit */
	return 0;
}
