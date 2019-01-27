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
#include <inttypes.h>

#define IS_DBG
#define BUF_SIZE 256

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

	char host_ip[1024];
	uint32_t ip;
	hostnameToIp(hostname, host_ip);
	#ifdef IS_DBG
	printf("host_ip = '%s'\n", host_ip);
	#endif
	inet_pton( AF_INET, host_ip, &(addr->sin_addr) );
	/*addr->sin_addr = htonl(addr->sin_addr) ;
	memcpy(addr->sin_addr, ,sizeof(ip));*/
	
	#ifdef IS_DBG
	printf("addr->sin_addr = '%x'\n", addr->sin_addr);
	#endif

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
	int con_ret ;
	if(  con_ret=connect(sock, (struct sockaddr *)addr, sizeof(*addr))<0  ){
		#ifdef IS_DBG
		printf("Could not connect...\n");
		#endif
		return con_ret ;
	}

	printf("Succesful connection...\n");
	return sock ;
}

int readLine(char *buf){
	char *pbuf = buf ;
	char c; 
	while( (c = getchar()) != '\n'){
		*pbuf++ = c ;
	}
	*pbuf = '\0' ;

	return  pbuf - buf ;
}

int main(int argc, char **argv){
	if(argc<3){
		printf("netcat: too few arguments");
		exit(1);
	}

	#ifdef IS_DBG
	printf("Program started.\n");
	#endif /* IS_DBG. */
	struct sockaddr_in *addr;
	int sock = createSocket(argv[1], atoi(argv[2]), &addr) ;

	if( connect(sock, (struct sockaddr *)addr, sizeof(*addr)) ){
		perror("connect");
		return 1 ;
	}

	char *buf = malloc(sizeof(char) * BUF_SIZE ) ;
	char *red = malloc(sizeof(char) * BUF_SIZE ) ;

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
	printf("Before loop...\n");
	#endif

	ssize_t bytes = 0 ;
	while(1){
		#ifdef IS_DBG
		printf("Inputing:");
		#endif
		readLine(red);
		#ifdef IS_DBG
		printf("Read to the buf '%s', sending now...\n", red);
		#endif
		send(sock, red, 1024, 0/*MSG_NOSIGNAL*/ );
		#ifdef IS_DBG
		puts("Sended! Recieving now...");
		#endif
		recv(sock, buf, 1024, 0);
		#ifdef IS_DBG
		printf("Printing:\n");
		#endif
		printf("%s\n", buf);
	}

	#ifdef IS_DBG
	puts("Before closing socket right now...");
	#endif
	close(sock);
	#ifdef IS_DBG
	puts("Closed socket...");
	#endif

	return 0;
}
