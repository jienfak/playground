#include <inttypes.h>

uint64_t strlen(char *str){
	char *pstr = str ;
	while(*pstr++){
		;
	}

	return pstr-str ;
}
