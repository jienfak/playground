#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char **argv){
	int sockfd, portno, n;
	struct sockaddr_in srv_addr;
	struct hostent *srv;

	char buf[256];
	if(argc<3){
		fprintf(stderr, "usage %s hostname port", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]) ;
	sockfd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sockfd<0){
		error("socket");
	}
	srv = gethostbyname(argv[1]) ;
	if(!srv){
		fprintf(stderr, "ERROR, no such host.\n");
		exit(0);
	}

	bzero((char *)&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET ;
	bcopy((char *)srv->h_addr,
		(char *)&srv_addr.sin_addr.s_addr,
		srv->h_length
	);
	srv_addr.sin_port = htons(portno) ;

	if( connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0 ){
		error("connect");
	}
	printf("Message:");
	bzero(buf, sizeof(buf));
	fgets(buf, sizeof(buf), stdin);
	n = send(sockfd, buf, strlen(buf), 0);
	if(n<0){
		error("send");
	}
	n = recv(sockfd, buf, sizeof(buf), 0);
	printf("%s", buf);

	return 0 ;
}
