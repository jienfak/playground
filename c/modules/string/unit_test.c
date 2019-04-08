#include <stdio.h>
#include "../string.h"

int main(int argc, char **argv){
	char **arr = {
			"1234", "5678",
			"abcdef", "hetuas",
			"fuckyou", "git123456"
		}
	;
	int size = sizeof(arr)/sizeof(char *) ;

	for( int i=0 ; i<size ; ++i ){
		printf("subCharArr: '%s' = %d ;", arr[i], subCharArr(arr[i], "123", strlen(arr[i]), 3) );
	}
	return 0 ;
}
