#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 2048
#define TRUE 1

int main(int argc, char **argv){
	printf("Server started...");
	int sock, listener;
	struct sockaddr_in addr;
	char buf[BSIZE];
	int bytes_read;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener<0){
		perror("socket");
		exit(1);
	}

	/* server options */
	addr.sin_family		= AF_INET;
	addr.sin_port		= htons(3425);

	addr.sin_addr.s_addr	= inet_addr("127.0.0.1");	
	/* connecting to the network device */
	if( bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0 ){
		perror("bind");
		exit(2);
	}


	listen(listener, 1);
	while(TRUE){
		sock = accept(listener, NULL, NULL);
		if(sock<0){
			perror("accept");
			exit(3);
		}

		switch( fork() ){
			case -1:
				perror("fork");
				break;
			case 0:
				close (listener);
				while(TRUE){
					printf("Waiting message...\n");

					bytes_read = recv(sock, buf, BSIZE, 0); /* getting msg */
					if( bytes_read <= 0 ){
						break;
					}
					printf("Got %d bytes\t MSG:'%s'", bytes_read, buf);
					
					printf("Sending this msg to the client");
					send(sock, buf, bytes_read, 0);
				}

				close(sock);
				_exit(0);

			default:
				close(sock);
		}
	}


	exit(0);
}
