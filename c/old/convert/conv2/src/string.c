#include "./header.h"

int strSwitch( char **strarr, int arrlen, char *str ){

	for(int i = 0; i<arrlen ; ++i){
		if(  !( strcmp(strarr[i], str) )  ){
			return i;
		}
	}

	return -1;
}

int chrSwitch(char *str, char chr){
	char *pstr = str;

	while(*pstr){
		if(chr==*pstr){
			return pstr-str;
		}
		++pstr;
	}

	return -1;
}

us_t isNum(char *str){

	while(*str){
		if( !isdigit(*str++) ){
			return FALSE;
		}
	}

	return TRUE;
}

us_t isKw(char *str){
	if( str && str[0]!='-' ){
		return TRUE;
	}else{
		return FALSE;
	}
}

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
