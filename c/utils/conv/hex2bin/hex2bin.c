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

int isChrInStr(char c, char *str){
	while(*str){
		if(c==*str++){
			return 1 ;
		}
	}
	return 0 ;
}

int main(int argc, char **argv){
	char *hex_chars = "0123456789ABCDEF" ;
	char c1=1, c2=1;
	for(;;){
		do{
			c1 = getchar() ;
			if(c1==EOF){
				goto EXIT;
			}
		}while(! isChrInStr(c1, hex_chars) );

		do{
			c2 = getchar() ;
			if(c2==EOF){
				goto EXIT;
			}
		}while(! isChrInStr(c2, hex_chars));
		printf("%c", hex2char(c1, c2));
	}
	/* Succesful exit. */
EXIT:
	return 0 ;
}
