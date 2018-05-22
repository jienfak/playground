#include <stdio.h>
#include <string.h>

int power(int num, int pow){
	int buff = 1;
	for(int i=0; i<pow ; ++i){
		buff*=num;
	}
	return buff;
}

char hex2ascii(char *hex){
	++hex;
	int buff = 0;
	for(int i=0; i<2 ; ++i){
		if('0'<=*hex && *hex<='9'){
			buff+=(*hex-'0') * power(16, i);
		}else{
			buff+=(*hex-'a'+10) * power(16, i);
		}
		--hex;
	}
	return buff;
}

int main(int argc, char **argv){
	char buff[1024];
	if(argc==1){
		printf("hex2ascii\t: too few arguments");
		return 1;
	}

	char *pcurrent = argv[1];
	int wordlen = strlen(argv[1]);
	if(wordlen%2){
		printf("hex2ascii\t:i 2");
		return 1;
	}

	for(int i=0 ; i<wordlen/2 ; ++i){
		buff[i] = hex2ascii(pcurrent);
		pcurrent+=2;
	}
	printf("'%s'\n", buff);
	//default exit
	return 0;
}
