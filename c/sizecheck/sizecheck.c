#include <stdio.h>

int main(int argc, char *argv[]){
	printf("Long	int 	size is '%d'\n", sizeof(long int));
	printf("Short	int 	size is '%d'\n", sizeof(short int));
	printf("Long	double	size is '%d'\n", sizeof(long double));
	printf("Short	double	size is '%d'\n", sizeof( double));
	printf("Char		size is '%d'\n", sizeof(char));
	//default exit 
	return 0;
};
