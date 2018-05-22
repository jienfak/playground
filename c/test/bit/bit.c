#include <stdio.h>

int getbit(int num, int bit){
	return (num>>bit)&1;
};

int main(int argc, char argv[]){
	printf("%d\n", getbit(1, 3));
	//exit
	return 0;
};
