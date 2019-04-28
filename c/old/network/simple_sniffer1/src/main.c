#include <stdio.h>        /* For standart things. */
#include <stdlib.h>       /* malloc */
#include <string.h>       /* memset */
#include <netinet/ip_icmp.h>     /* ICMP hea. */
#include <netinet/udp.h>         /* UDP header declaration. */
#include <netinet/tcp.h>         /* TCP header declaration. */
#include <sys/socket.h>          /* IP  header declaration. */
#include <arpa/inet.h>           /*                         */
#include <unistd.h>

#define ICMP_PROTO 1
#define IGMP_PROTO 2
#define TCP_PROTO  6
#define UDP_PROTO  17

void processPacket(unsigned char *, int);
void printIpHeader(unsigned char *, int);
void printTcpPacket(unsigned char *, int);
void printUdpPacket(unsigned char *, int);
void printIcmpPacket(unsigned char *, int);
void printData(unsigned char *, int);

int sock_raw;
FILE *logfile;
int tcp=0, udp=0, icmp=0, others=0, igmp=0, total=0, i, j ;
struct sockaddr_in src, dest;

int main(){
	int saddr_size, data_size;
	struct sockaddr saddr;
	struct in_addr in;
	unsigned char *buf = (unsigned char *)malloc(256*256) ;

	logfile = fopen("log.txt", "w") ;
	if(logfile==NULL){
		puts("Unable to create log file.");
	}

	puts("Starting...");

	sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP) ;
	if(sock_raw < 0){
		printf("Socket error.");
		return 1 ;
	}

	while(1){
		saddr_size = sizeof saddr ;

		/* Recieve packet. */
		data_size = recvfrom(sock_raw, buf, 256*256, 0, &saddr, &saddr_size) ;
		if( data_size < 0 ){
			puts("recvfrom error, failed to get packets");
			return 1 ;
		}

		/* Packet processing */
		processPacket(buf, data_size);
	}
	close(sock_raw);
	puts("Finished.");
	return 0 ;
}

void processPacket(unsigned char *buf, int size){
	/* Get the IP header part of this packet. */
	struct iphdr *iph = (struct iphdr *)buf ;
	++total;
	switch(iph->protocol){
		case TCP_PROTO  :
			++tcp;
			printTcpPacket(buf, size);
			break;
		case ICMP_PROTO :
			++icmp;
			break;
		case IGMP_PROTO :
			++igmp;
			break;
		case UDP_PROTO :
			++udp;
			printUdpPacket(buf, size);
			break;
		default:
			++others;
			break;
	}
	printf("TCP : %d UDP : %d ICMP : %d IGMP : %d Others : %d Total : %d\r", tcp, udp, icmp, igmp, others, total);
}

void printIpHeader(unsigned char *buf, int size){
	unsigned short ip_hdr_len;
	struct iphdr *iph = (struct iphdr *)buf ;

	memset(&src, 0, sizeof(src));
	src.sin_addr.s_addr = iph->saddr ;

	fprintf(logfile, "\n");
	fprintf(logfile, "IP Header");
	fprintf(logfile, "   |-IP version             : %d\n", (unsigned int)iph->version);
	fprintf(logfile, "   |-IP header length       : %d bytes\n", (unsigned int)iph->ihl);
	fprintf(logfile, "   |-IP type of service     : %d\n", (unsigned int)iph->tos );
	fprintf(logfile, "   |-Identification         : %d\n", ntohs(iph->id));
	/*fprintf(logfile, "   |-IP reserved ZERO field : %d\n", (unsigned int)iph->ip_reserved_zero);
	fprintf(logfile, "   |-Don't fragment field   : %d\n", (unsigned int)iph->ip_dont_fragment);
	fprintf(logfile, "   |-More fragment field    : %d\n", (unsigned int)iph->ip_more_fragment);*/
	fprintf(logfile, "   |-TTL                    : %d\n", (unsigned int)iph->ttl);
	fprintf(logfile, "   |-Protocol               : %d\n", (unsigned int)iph->protocol);
	fprintf(logfile, "   |-Checksum               : %d\n", (unsigned int)ntohs(iph->check));
	fprintf(logfile, "   |-Source IP              : %s\n", inet_ntoa(src.sin_addr));
	fprintf(logfile, "   |-Destination IP         : %s\n", inet_ntoa(dest.sin_addr));
}

void printTcpPacket(unsigned char * buf, int size){
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)buf ;
	iphdrlen = iph->ihl*4 ;

	struct tcphdr *tcph = (struct tcphdr *)(buf + iphdrlen) ;

	fprintf(logfile, "\n\n**************TCP packet**************\n");
	printIpHeader(buf, size);
	fprintf(logfile, "\n");
	fprintf(logfile, "    |-Source port          : %u\n", ntohs(tcph->source));
	fprintf(logfile, "    |-Destination port     : %u\n", ntohs(tcph->dest));
	fprintf(logfile, "    |-Sequence number      : %u\n", ntohl(tcph->seq));
	fprintf(logfile, "    |-Acknowledge number   : %u\n", ntohl(tcph->ack_seq));
	fprintf(logfile, "    |-Header length        : %d\n", (unsigned int)tcph->doff*4);
	fprintf(logfile, "    |-Urgent flag          : %d\n", (unsigned int)tcph->urg);
	fprintf(logfile, "    |-Acknowledgement flag : %d\n", (unsigned int)tcph->ack);
	fprintf(logfile, "    |-Push flag            : %d\n", (unsigned int)tcph->psh);
	fprintf(logfile, "    |-Reset flag           : %d\n", (unsigned int)tcph->rst);
	fprintf(logfile, "    |-Finish flag          : %d\n", (unsigned int)tcph->fin);
	fprintf(logfile, "    |-Window               : %d\n", htons(tcph->window));
	fprintf(logfile, "    |-Checksum             : %d\n", ntohs(tcph->check));
	fprintf(logfile, "    |-Urgent pointer       : %d\n", tcph->urg_ptr);
	fprintf(logfile, "\n");
	fprintf(logfile, "              DATA DUMP             ");
	fprintf(logfile, "IP header");
	printData(buf, iphdrlen);

	fprintf(logfile, "TCP header");
	printData(buf+iphdrlen, tcph->doff*4 );

	fprintf(logfile, "Data payload");
	printData(buf + iphdrlen + tcph->doff*4, (size - tcph->doff*4 - iph->ihl*4 ));
	fprintf(logfile, "\n################################\n");
}

void printUdpPacket(unsigned char *buf, int size){
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)buf ;
	iphdrlen = iph->ihl*4;

	struct udphdr *udph = (struct udphdr *)(buf + iphdrlen) ;
	fprintf(logfile, "\n\n******************* UDP packet ***************************");
	printIpHeader(buf, size);

	fprintf(logfile, "\nUDP header\n");
	fprintf(logfile, "    |-Source port       : %d\n", ntohs(udph->source));
	fprintf(logfile, "    |-UDP length        : %d\n", ntohs(udph->len));
	fprintf(logfile, "    |-UDP checksum      : %d\n", ntohs(udph->check));

	fprintf(logfile, "\n");
	fprintf(logfile, "IP header\n");
	printData(buf, iphdrlen);

	fprintf(logfile, "UDP header");
	printData(buf+iphdrlen, sizeof(udph));

	fprintf(logfile, "\nData payload\n");
	printData(buf + iphdrlen + sizeof(udph), (size - sizeof(udph) - iph->ihl*4 ));
	fprintf(logfile, "##############################################################");
}

void printIcmpPacket(unsigned char *buf, int size){
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)buf;
	iphdrlen = iph->ihl*4 ;

	struct icmphdr *icmph = (struct icmphdr *)(buf + iphdrlen) ;

	fprintf(logfile, "\n\n******************* ICMP packet **************************\n");
	printIpHeader(buf, size);

	fprintf(logfile, "ICMP header");
	fprintf(logfile, "    |-Code          : %d\n", (unsigned int)icmph->code);
	fprintf(logfile, "    |-Checksum      : %d\n", ntohs(icmph->checksum));
	/*fprintf(logfile, "    |-ID            : %d\n", ntohs(icmph->id)); */
	fprintf(logfile, "\n");
	fprintf(logfile, "IP header");
	printData(buf, iphdrlen);
	fprintf(logfile, "UDP header\n");
	printData(buf + iphdrlen, sizeof(icmph));
	fprintf(logfile, "Data payload\n");
	printData(buf + iphdrlen + sizeof(icmph), (size - sizeof(icmph) - iph->ihl*4 ));
	fprintf(logfile, "\n###############################333333####################");
}

void printData(unsigned char *data, int size){
	for( int i=0 ; i<size ; ++i){
		if( i && i%16==0){
			/* If the line of hex printing is complete... */
			fprintf(logfile, "    ");
			for( int j=i-16 ; j<i ; ++j){
				if(data[j]<=32 && data[j]<=128){
					/* If it's number or aplhabet. */
					fprintf(logfile, "%c", (unsigned char)data[j]);
				}else{
					/* Otherwise. */
					fprintf(logfile, ".");
				}
				fprintf(logfile, "\n");
			}

			if( i==size-1 ){
				/* Print the last spaces. */
				for( j=0 ; j<16-i%16 ; ++j){
					/* Extra spaces. */
					fprintf(logfile, " ");
				}
				fprintf(logfile, "    ");
				
				for( int j=i-i%16 ; i<=i ; j++){
					if(data[j]>=32 && data[j]<=128){
						fprintf(logfile, "%c", (unsigned char)data[j]);
					}else{
						fprintf(logfile, ".");
					}
				}
				fprintf(logfile, "\n");
			}
		}
	}
}
