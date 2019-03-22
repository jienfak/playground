#include <stdio.h>



char *char2HEX(char *dst, char c){
	/* Converts gotten char to hex into 'dst' pointer and returns it. */
	char first = (char)(c&0b11110000)>>4 ;/* Getting first half. */
	char second= (char)(c&0b00001111)    ;/* Getting second half.*/
	if(first<10){
		/* From 0 to 9. */
		*dst = '0' + first ;
	}else{
		/* From A to F. */
		*dst = 'A' + first - 10 ;
	}

	if(second<10){
		*(dst+1) = '0' + second ;
	}else{
		*(dst+1) = 'A' + second - 10 ;
	}

	return dst ;
}

int main(int argc, char **argv){
	int c;
	char buf[3]; buf[2] = '\0' ;
	while((c = getchar()) != EOF ){
		char2HEX(buf, (char)c);
		buf[2]='\0';
		printf("%s", buf);
	}
	/* Successful exit. */
	return 0 ;
}
