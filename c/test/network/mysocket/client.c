#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

char msg[] = "Hello, World!\n";
char buf[ sizeof(msg) ];

int main(int argc, char **argv){
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);

	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(  connect(sock, &addr, sizeof(addr) )  ){
		perror("connect");
		exit(2);
	}

	send(sock, msg, sizeof(msg), 0 );
	recv(sock, buf, sizeof(msg), 0);
	close(sock);

	printf(buf);

	return 0;

}
