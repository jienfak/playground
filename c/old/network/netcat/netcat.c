#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define IS_DBG

char msg[] = "Hello, World!\n";
char red[1024];



int hostnameToIp(char *hostname, char *ip){
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if(  !( he = gethostbyname(hostname) )  ){
		/* Get the host info. */
		herror("gethostbyname");
		return 1 ;
	}

	addr_list = (struct in_addr **)he->h_addr_list ;

	for( i=0 ; addr_list[i] ; ++i ){
		/* Return the first one. */
		strcpy( ip, inet_ntoa(*addr_list[i]) );
		return 0 ;
	}

	return 1 ;
}

int createSocket(char *hostname, int port, struct sockaddr_in **sockaddr){
	/*
	 * Frontend for all socket operations.
	 * Returns socket's descriptor or negative value if the error.
	 */
	
	int sock = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sock<0){
		/* Could not create socket for some reason. */
		return sock;
	}

	struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in)) ;
	addr->sin_family = AF_INET ;
	addr->sin_port   = port    ;

	char host_ip[1024];
	hostnameToIp(hostname, host_ip);
	inet_pton( AF_INET, host_ip, &(addr->sin_addr) );

	*sockaddr = addr ;
	#ifdef IS_DBG
	printf("addr = '%x'\n", addr);
	#endif
	return sock ;
}

int createConnection(char *hostname, int port){
	struct sockaddr_in *addr;
	int sock = createSocket(hostname, port, &addr) ;
	#ifdef IS_DBG
	printf("addr = '%x'\n", addr);
	printf("sock = '%d'\n", sock);
	#endif
	if(  connect(sock, (struct sockaddr *)addr, sizeof(addr))<0  ){
		#ifdef IS_DBG
		printf("Could not connect...\n");
		#endif
		return -1 ;
	}

	return sock ;
}

int main(int argc, char **argv){
	if(argc<3){
		printf("netcat: too few arguments");
		exit(1);
	}

	#ifdef IS_DBG
	printf("Program started.\n");
	#endif /* IS_DBG. */

	int sock = createConnection(argv[1], atoi(argv[2])) ;
	char buf[1024];

	printf("%d\n", sock);
	
	/*struct addrinfo res;
	struct addrinfo *result;*/

	/* IP getting. */
	
	/*err = getaddrinfo(argv[1], NULL, NULL, &result);
	if( err ){
		if(err == EAI_SYSTEM){
			perror("getaddrinfo");
		}else{
			fprintf( stderr, "error int getaddinfo: %s\n", gai_strerror(err) );
		}
		exit(EXIT_FAILURE);
	}

	addr.sin_addr.s_addr = ntohl(
		(
			(struct sockaddr_in *)( (struct addrinfo *)result )
				->
			ai_addr  
		)
			->
		sin_addr.s_addr
	) ; */

	#ifdef IS_DBG
	printf("before loop");
	#endif

	while(1){
		scanf("%s\n", red);
		send(sock, red, 1024, 0 );
		recv(sock, buf, 1024, 0);
		printf("%s", buf);
	}
	close(sock);

	return 0;
}
