#include <stdio.h>

#define REPEAT_N_TIMES(n, $code_block) \
	for(int i=0 ; i<n ; ++i){    \
		$code_block;         \
	}                            \

int main(int argc, char **argv){
	REPEAT_N_TIMES(4, printf("Hello, World!\n"));
	
	/* Exit. */
	return 0 ;
}
