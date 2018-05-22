#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

char message[] = "Hello, World!\n";
char buff[sizeof(message)];

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
	if(  connect(sock, ( struct sockaddr *)&addr, sizeof(addr) )<0  ){
		perror("connect");
		exit(2);
	}

	send( sock, message, sizeof(message), 0 );
	recv( sock, buff, sizeof(message), 0 );
	
	printf(buff);
	close(sock);
	//default exit of program
	return 0;
}

