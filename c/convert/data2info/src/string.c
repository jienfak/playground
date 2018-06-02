#include "./header.h"

int str_switch( char **strarr, int arrlen, char *str ){

	for(int i = 0; i<arrlen ; ++i){
		if(  !( strcmp(strarr[i], str) )  ){
			return i;
		}
	}

	return -1;
}

int chr_switch(char *str, char chr){
	char *pstr = str;

	while(*pstr){
		if(chr==*pstr){
			return pstr-str;
		}
		++pstr;
	}

	return -1;
}

char *strlow(char *dest, char *src){
	char *pdest = dest;
	/* difference between lower and upper cases */
	int8_t bias = 'a' - 'A' ;

	while(*pdest){
		if( *pdest>="A" *pdest<="Z"){
			*pdest = *pdest + bias ;
		}		
		++pdest;
	}

	return (char *)dest;
}

char *strup(char *dest, char *src){
	char *pdest = dest;
	/* difference between lower and upper cases */
	int8_t bias = 'a' - 'A' ;

	while(*pdest){
		if( *pdest>="a" *pdest<="z"){
			*pdest = *pdest - bias ;
		}		
		++pdest;
	}

	return (char *)dest;
}


int grpsize(char **group){
	t_ul i = 0;

	while(*group){
		++group, ++i;
	}

	return i;
}

/* it's not needed here
 *
t_us isnum(char *str){

	while(*str){
		if( !isdigit(*str++) ){
			return FALSE;
		}
	}

	return TRUE;
}

t_us iskw(char *str){
	if( str && str[0]!='-' ){
		return TRUE;
	}else{
		return FALSE;
	}
}
*
*/

