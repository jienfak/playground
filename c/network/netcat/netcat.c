#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

char msg[] = "Hello, World!\n";
char buf[1024];
char red[1024];

int main(int argc, char **argv){
	if(argc<3){
		printf("netcat: too few arguments");
		exit(1);
	}

	printf("Program started.\n");
	int sock, err;
	struct sockaddr_in addr;
	struct addrinfo res;
	struct addrinfo *result;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET ;
	addr.sin_port = htons(atoi(argv[2])) ;

	err = getaddrinfo(argv[1], NULL, NULL, &result);
	if( err ){
		if(err == EAI_SYSTEM){
			perror("getaddrinfo");
		}else{
			fprintf( stderr, "error int getaddinfo: %s\n", gai_strerror(err) );
		}
		exit(EXIT_FAILURE);
	}

	addr.sin_addr.s_addr = htonl(
		(
			(struct sockaddr_in *)( (struct addrinfo *)result )
				->
			ai_addr  
		)
			->
		sin_addr.s_addr
	) ;
	printf("Connecting to '0x%x'...\n", addr.sin_addr.s_addr);
	if(  connect(sock, (struct sockaddr *)&addr, sizeof(addr))<0  ){
		perror("connect");
		exit(2);
	}

	printf("before loop");
	while(1){
		printf("reading something: ");
		scanf("%s\n", red);
		send(sock, red, 1024, 0 );
		printf("sended...\n");


		printf("reading...\n");
		recv(sock, buf, 1024, 0);
		printf("got msg...\n");
		printf("%s\n", buf);
	}
	close(sock);

	return 0;
}
