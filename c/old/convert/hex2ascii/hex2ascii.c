#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUFFSIZE 1024

int power(int num, int pow){
	int buff = 1;
	for(int i=0; i<pow ; ++i){
		buff*=num;
	}
	return buff;
}

char hex2char(char *phex){
	char c = 0;
	for(int i=1; 0<=i ; --i){
		if( phex[i]>='0' && phex[i]<='9'  ){
			c += power(16, 1-i) * (phex[i]-'0') ;
		}else if( phex[i]>='a' && phex[i]<='z'){
			c += power(16, 1-i) * (phex[i]-'a'+10) ;
		}else if( phex[i]>='A' && phex[i]<='Z'){
			c += power(16, 1-i) * (phex[i]-'A'+10) ;
		}else{
			/* nothing */
		}
	}
}

void hex2ascii( char *pbuff, char *phex ){
	while(*phex){
		*pbuff++ = hex2char(phex);
		++phex;
		if(!*phex){
			break;
		}
		++phex;
	}

	*pbuff = '\0';
}

int main(int argc, char **argv){
	char buff[BUFFSIZE];

	hex2ascii(buff, argv[1]);
	printf( "%s", buff, strlen(buff) );
	/* default exit */
	return 0;
}
