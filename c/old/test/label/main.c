#include <stdio.h>

int main(int argc, char **argv){
	label:
	printf("&label = %p\n", &&label);
	return 0 ;
}
