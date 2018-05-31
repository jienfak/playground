#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(void){
	int sock, listener;
	struct sockaddr_in addr;
	char buff[1024];
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

	while(1){
		sock = accept(listener, NULL, NULL);
		if(sock <0){
			perror("accept");
		}

		while(1){
			bytes_read = recv(sock, buff, 1024, 0);
			if(bytes_read<=0){
				break;
			}
			send(sock, buff, bytes_read, 0);
		}

		close(sock);
	}

	return 0;
}