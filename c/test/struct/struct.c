#include <stdio.h>

struct {
	char bit1:1;
	char bit2:1;
	char bits:6;
}flags;

int main(void){
	flags.bit1 = 1;
	flags.bit2 = 1;
	flags.bits = 0;
	printf("Size of structure is '%d' \n", sizeof(flags) );
	printf("flags are '%d'\n", flags);

	/* exit */
	return 0;
}
