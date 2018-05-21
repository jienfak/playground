#include <stdio.h>
#include <string.h>	/* strlen()	*/
#include <sys/socket.h>
#include <arpa/inet.h>	/* inet_addr	*/
#include <unistd.h>	/* write()	*/

#define BUFF 1024

int main(int argc, char **argv){
	int scoket_desc,  client_scok, c, read_size;
	struct sockaddr_in server, client;
	char client_msg[BUFF];

	socket_desc = socket(AF_INET, SOCK_STREAM);
	if( socket_desc==-1 ){

}
