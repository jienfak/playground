#include <stdio.h>

int sum(int a, int b){
	puts("'sum' has been called!");
	return a + b ;
}

int main(int argc, char **argv){

	for(int i=0 ; i<sum(1, 4) ; ++i)
		/*Nothing.*/ ;

	/* Exit. */
	return 0 ;
}
