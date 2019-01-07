#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv){
	int i = ( true
			?
		12345
			:
		6789
	);

	printf("%d\n", i);
	/* exit */
	return 0;
}
