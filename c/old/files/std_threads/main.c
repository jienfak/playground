#include <stdio.h>

int main(int argc, char **argv){
	puts("You should can read that!");

	char buf[64];
	puts("Something!");
	int read_bytes = fread( (void *)buf, sizeof(char), 64, stdout);
	printf("%s", buf);
	/* exit */
	return 0 ;
}
