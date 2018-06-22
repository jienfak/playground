#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PROGNAME "exec"

int main(int argc, char **argv){
	if(argc<2){
		printf("%s: too few arguments\n", PROGNAME);
		exit(1);
	}

	execve( argv[1], argv+2, NULL );
	printf("Hello, World!\n");
	return 0;
}
