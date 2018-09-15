#include <stdio.h>

int main(int argc, char **argv){
	char buf[1024];
	fwrite("You suck!", sizeof(char), sizeof("You suck!"), stdout);
	fread(buf, sizeof(char), sizeof("You suck!"), stdout);
	printf("\n'%s'.\n", buf);
	/* Succesfull exit. */
	return 0 ;
}
