#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 64
#define STDERR 2
#define STDOUT 1
#define STDIN 0
#define PROMPT ">"

/* reads from 'fd' to 'buf' all before 'endchr' */
int readLine(int fd, char *const buf, char end_chr){
	char *pbuf = buf ;
	char cont_chr;

	do{
		read(fd, &cont_chr, 1);
		*pbuf++ = cont_chr ;
	}while(cont_chr && (cont_chr != end_chr));

	*(pbuf-1) = '\0' ;

	return pbuf - buf - 1 ;
}

/* prints C-string to STDOUT */
void printStr(char *str){
	write(STDOUT, str, strlen(str) );
}

int strlenByChr(char *str, char end){
	char *pstr = str ;
	while(*pstr && (*pstr != end) ){
		++pstr;
	}
	return pstr-str ;
}



/* parsing by separator to dst */
char **sepParse(char **dst, char *str, char sep, int len){
	int cur_str = 0 ;
	int cur_dst = 0 ;

	while(cur_str<len){
		if(!(str[cur_str] == sep)){
			int word_len = strlenByChr( str+cur_str, sep) ;
			strncpy( dst[cur_dst], str+cur_str, word_len );
			dst[cur_dst][word_len+1] = '\0' ;

			cur_str += word_len ;
			++cur_dst;

		}else{
			++cur_str;
		}
	}

	return dst ;
}

int main(int argc, char **argv){
	char com[BUF_SIZE];
	char *com_parsed[BUF_SIZE];
	for(int i=0; i<BUF_SIZE ; ++i){
		com_parsed[i] = (char *)malloc(BUF_SIZE * sizeof(char));
	}

	int com_len, exit_code;
	while(true){
		printStr(PROMPT);
		com_len = readLine(STDIN, com, '\n') ;
		sepParse(com_parsed, com, ' ', com_len);
		printf("Executing '%s'...\n", com_parsed[0]);
		int status, options;
		pid_t pid;
		switch( pid = fork() ){
			case -1:
				perror("fork");
				break;
			case 0:
				exit_code = execve(com_parsed[0], com_parsed, NULL );
				printf("I'm a child! \n");
				exit(0);
				break;
			default:
				waitpid(pid, &status, 0);
				printf("Return code = '%d'.", exit_code);
				break;
		}	
	}

	/* default exit */
	return 0;
}
