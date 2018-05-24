#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <<netdb.h>
#include <stdio.h>
#include <ctype.h>

char msg[] = "Hello, World!\n";
char buf[1024];
char red[1024];

int main(int argc, char **argv){
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons( atoi(argv[2]) );

	addr.sin_addr.s_addr = htonl( argv[1] );
	if(  connect(sock, &addr, sizeof(addr) )  ){
		perror("connect");
		exit(2);
	}

	while(1){
		scanf("%s\n", red);
		send(sock, red, sizeof(msg), 0 );

		recv(sock, buf, sizeof(msg), 0);
		printf("%s", buf);
	}
	close(sock);

	return 0;

}
