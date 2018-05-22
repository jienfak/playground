#include <stdio.h>

int strln(char *str){
	char *pfrst = str;
	while(*str){
		++str;
	}
	return str-pfrst;
}

int main(int argc, char **argv){
	printf("%d\n", strln(argv[1]));
	return 0;
}
