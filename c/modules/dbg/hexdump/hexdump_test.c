#include "../hexdump.h"

#if defined(main)
/* Nothing. */
#else
#define __MAIN_FUNC
#include <string.h>
int main(int argc, char **argv){
	for(uint64_t i=1 ; i<argc ; ++i ){
		printf("%d argument hex dump:\n", i);
		hexdump(argv[i], strlen(argv[i]));
	}

	char buf[1024];
	int16_t size=16 ;
	while( read(0, buf, 1024) > 0 ){
		hexdump(buf, 1024);
	}

	return 0 ;
}
#endif /* __MAIN_FUNC */
