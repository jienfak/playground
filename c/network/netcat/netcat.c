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
	int sock, err;
	struct sockaddr_in addr;
	struct addrinfo *res;
	struct addrinfo *result;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons( atoi(argv[2]) );

	err = getaddrinfo(argv[1], NULL, NULL, &result);
	if( err ){
		if(err == EAI_SYSTEM){
			perror("getaddrinfo");
		}else{
			fprintf( stderr, "error int getaddinfo: %s\n", gai_strerror(err) );
		}
		exit(EXIT_FAILURE);
	}

	for(res = result; res != NULL; res = res->ai_next){
		char hostname[NI_MAXHOST];
		err = getnameinfo(	
				res->ai_addr, res->ai_addrlen, hostname, NI_MAXHOST,
				NULL, 0, 0			
		);

		if(err) {
			fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(err) );
			continue;
		}

		if(*hostname != '\0'){
			printf("hostname: '%s'\n", hostname);
		}
	}


	addr.sin_addr.s_addr = htonl( ((struct sockaddr_in  *)result->ai_addr)->sin_addr.s_addr );
	if(  connect(sock, (struct sockaddr *)&addr, sizeof(addr) )  ){
		perror("connect");
		exit(2);
	}

	while(1){
		scanf("%s\n", red);
		send(sock, red, sizeof(msg), 0 );

		recv(sock, buf, sizeof(msg), 0);
		printf("%s\n", buf);
	}
	close(sock);

	return 0;

}
