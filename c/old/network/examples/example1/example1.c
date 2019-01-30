#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *msg, int exit_code){
	perror(msg);
	exit(0);
}

int crtSocket(char *host, int portno, struct sockaddr_in **psrv_addr){
	int sockfd;
	struct hostent *srv;
	struct sockaddr_in *srv_addr = malloc(sizeof(struct sockaddr_in)) ;

	sockfd =  socket(AF_INET, SOCK_STREAM, 0) ;
	if( sockfd<0 ){
		return sockfd ;
	}

	srv = gethostbyname(host) ;

	bzero((char *)srv_addr, sizeof(srv_addr));
	srv_addr->sin_family = AF_INET ;
	bcopy((char *)srv->h_addr,
		(char *)&srv_addr->sin_addr.s_addr,
		srv->h_length
	);
	srv_addr->sin_port = htons(portno) ;
	*psrv_addr = srv_addr ;

	return sockfd ;
}

int crtConnection(char *host, int port){
	struct sockaddr_in *srv_addr;
	int sockfd = crtSocket(host, port, &srv_addr) ;

	int c ;
	if( (c = connect(sockfd, (struct sockaddr *)srv_addr, sizeof(*srv_addr)) ) < 0 ){
		return c ;
	}

	return sockfd ;
}

int main(int argc, char **argv){
	int sockfd, portno, n;
	struct sockaddr_in *srv_addr;

	char buf[256];
	if(argc<3){
		fprintf(stderr, "usage %s hostname port", argv[0]);
		exit(0);
	}	

	sockfd = crtConnection(argv[1], atoi(argv[2])) ;

	/*portno = atoi(argv[2]) ;
	sockfd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sockfd<0){
		error("socket");
	}
	srv = gethostbyname(argv[1]) ;

	bzero((char *)&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET ;
	bcopy((char *)srv->h_addr,
		(char *)&srv_addr.sin_addr.s_addr,
		srv->h_length
	);
	srv_addr.sin_port = htons(portno) ;*/


	/*printf("Message:");*/
	n = 1 ; /* For start. */
	while(n){
		bzero(buf, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		n = send(sockfd, buf, strlen(buf), 0);
		if(n<0){
			error("send", 3);
		}
		n = recv(sockfd, buf, sizeof(buf), 0);
		printf("%s", buf);
	}

	return 0 ;
}
