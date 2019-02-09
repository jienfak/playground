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
	/* Create socket to the host routine. */
	int sockfd;
	struct hostent *srv;
	struct sockaddr_in *srv_addr = malloc(sizeof(struct sockaddr_in)) ;

	sockfd =  socket(AF_INET, SOCK_STREAM, 0) ;
	if( sockfd<0 ){
		return sockfd ;
	}

	srv = gethostbyname(host) ;
	if(!srv){
		printf("Could not find host.\n");
	}

	/* Clearing addr_in structure to do not get errors. */
	bzero((char *)srv_addr, sizeof(srv_addr));
	/* Settting address family. */
	srv_addr->sin_family = AF_INET ;
	/* Copying bin IP-address to the out sockaddr_in structure for socket. */
	bcopy((char *)srv->h_addr,
		(char *)&srv_addr->sin_addr.s_addr,
		srv->h_length
	);
	/* Port setting. */
	srv_addr->sin_port = htons(portno) ;
	/* Returning our structure created to continue work with that. */
	*psrv_addr = srv_addr ;

	return sockfd ;
}

int crtConnection(char *host, int port){
	/* Create socket connect to the host, return error if could not. */
	struct sockaddr_in *srv_addr;
	int sockfd = crtSocket(host, port, &srv_addr) ;
	if(sockfd<0){
		return sockfd ;
	}

	int c; /* Connect return.  */
	if( (c = connect(sockfd, (struct sockaddr *)srv_addr, sizeof(*srv_addr)) ) < 0 ){
		return c ;
	}

	return sockfd ;
}

void readEOF(char *buf, ssize_t size){
	char c;
	char *pbuf = buf ;
	while( (c=getchar())!=EOF && (pbuf-buf)<size){
		*pbuf++ = c ;
	}
	*pbuf = '\0' ;
}

int main(int argc, char **argv){
	int sockfd, portno, n;
	struct sockaddr_in *srv_addr;

	char buf[1024];
	if(argc<3){
		fprintf(stderr, "usage %s hostname port", argv[0]);
		exit(0);
	}	

	sockfd = crtConnection(argv[1], atoi(argv[2])) ;
	if(sockfd<0){
		error("socket", 1);
	}

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
	char rbuf[1024];
	while(1){
		bzero(buf, sizeof(buf));
		bzero(rbuf, sizeof(rbuf));
		readEOF(buf, sizeof(buf));
		strcat(buf, "\n");

		n = send(sockfd, buf, strlen(buf), 0);
		if(n<0){
			error("send", 3);
		}
		while(n){
			n = recv(sockfd, rbuf, sizeof(rbuf), 0);
			printf("%s", rbuf);
		}		
	}

	return 0 ;
}
