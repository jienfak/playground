#include <stdio.h>
#include <string.h>

char hex2char(char a, char b){
	char a_ret = 0 ;
	if(('0'<=a)&&(a<='9')){
		a_ret = a - '0';
	}else if(('A'<=a)&&(a<='F')){	
		a_ret = a-'A'+10 ;
	}
	a_ret <<= 4 ;

	char b_ret = 0 ;
	if(('0'<=b)&&(b<='9')){
		b_ret = b - '0';
	}else if(('A'<=b)&&(b<='F')){	
		b_ret = b-'A'+10 ;
	}

	return a_ret | b_ret ;
}


int main(int argc, char **argv){
	char c1, c2;
	while((c1=getchar())!=EOF && (c2=getchar())!=EOF){
		printf("%c", hex2char(c1, c2));
	}
	/* Succesful exit. */
	return 0 ;
}
