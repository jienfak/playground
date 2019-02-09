#include <stdio.h>

int a(void){
	puts("Calling 'a'.");
}
int b(void){
	puts("Calling 'b'.");
}
int c(void){
	puts("Calling 'c'.");
}

int func(int a, int b, int c){
	printf("Called func.");
}

int main(int argc, char **argv){
	func(a(), b(), c());
	return 0 ;
}
