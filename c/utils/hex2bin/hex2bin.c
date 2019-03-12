#include <stdio.h>
#include <string.h>


int main(int argc, char **argv){
	char buf[sizeof(unsigned int)+1]; buf[sizeof(unsigned int)] = '\0' ;
	while(scanf("%x", buf)!=EOF){
		printf("%s", buf);
	}
	/* Succesful exit. */
	return 0 ;
}
