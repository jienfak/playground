#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <features.h>
#include <linux/if_packet.h>
/*#include <linux/if_ether>*/
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <netinet/in.h>
/*#include <libipq.h>*/
#define BUF_SIZE =2048

int sd;

int createRawSocket(int protocol_to_sniff){
	int rawsock;
	if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff)))==-1){
		perror("socket");
		exit(-1)
	}
	return rawsock ;
}

int bindRawSocketToInterface(char *device, int rawsock, int protocol){
	struct sockaddr_ll sll;
	struct ifreq ifr;
	bzero(&sll, sizeof(sll));
	bzero(&ifr, sizeof(ifr));

	/* First - get the Interface index. */
	strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
	if( ioctl(rawsock, SIOCGFINDEX, &ifr) == -1){
		puts("interface: getting problem.");
		exit(-1);
	}

	/* Bind raw socket to this interface. */
	sll.sll_family = AF_PACKET ;
	sll.sll_ifindex = ifr.ifr_ifindex ;
	sll.sll_protocol = htons(protocol) ;

	if( bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)) == -1 ){
		perror("bind");
		exit(-1);
	}

	return -1 ;
}

void printPacketInHex(unsigned char *packet, int len){
	unsigned char *p = packet ;
	printf("----Packet-start----\n");
	while(len--){
		printf("%.2x", *p);
		p++
	}
	printf("----Packet-end----\n");
}

void printInHex(char *msg, char *p, int len){
	printf("%s", msg);
	while(len--){
		printf("%.2x", *p);
		p++;
	}
}

void parseEthernetHeader(char *packet, int len){
	struct ethhdr *ethernet_header;
	if(len>sizeof(struct ethhdr)){
		ethernet_header = (struct ethhdr *)packet ;
		printInHex("Destination MAC: ", ethernet_header->h_dest, 6);
		puts("");
		printInHex("Source MAC", ethernet_header->h_source, 6);
		puts("");
		printInHex("Protocol: ", (void *)&ethernet_header->h_proto, 2);
		puts("");
	}else{
		puts("Packet is too small!!!");
	}
}
void parseIpHeader(char *packet, int len){
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;
	/* First check if the packet contains an IP header using the Ethernet header. */
	ethernet_header = (struct ethhdr *)packet ;
	if( ntohs(ethernet_header->h_proto) == ETH_P_IP ){
		/* IP header is after Ethernet header. */
		if( len>=(sizeof(struct ethhdr) + sizeof(struct iphdr)) ){
			printf("Dest IP address: %s\n", inet_ntoa(ip_header->daddr));
			printf("Src  IP adderss: %s\n", inet_ntoa(ip_header->saddr));
		}else{
			puts("IP packet does not contain full header.");
		}
	}
}

void parseTcpHeader(char *packet, int len){
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;
	/* Check if enough byets are there for TCP header. */

	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr), + sizeof(struct tcphdr))){
		/*
		 * Do all the checks:
		 * 1. Is it an IP packet?
		 * 2. Is it TCP?
		 */
		ethernet_header = (struct ethhdr *)packet ;
		if(ntohs(ethernet_header->h_proto)==ETH_P_IP){
			ip_header = (struct iphdr *)(packet + sizeof(struct ethhdr)) ;
			if(ip_header->protocol == IPPROTO_TCP){
				tcp_header = (struct tcphdr *)(packet + sizeof(struct ethhdr) + ip_header->ihl*4) ;
				
				/* Printing Dest and Src ports. */
				printf("Source Port: %d\n", ntohs(tcp_header->source));
				printf("Dest   Port: %d\n", ntohs(tcp_header->dest));
			}else{
				puts("It's not TCP packet.");
			}
		}else{
			puts("TCP header isn't present.");
		}
	}
}

int main(int argc, char **argv){
	int raw;
	char packet_buf[2048];
	int len;
	int packets_to_sniff;
	struct sockaddr_ll packet_info;
	int packet_info_size = sizeof(packet_info) ;

	/* Creating raw socket. */
	raw = createRawSocket(ETH_P_IP) ;
	/* Binding to interface.*/
	bindRawSocketToInterface(argv[1], raw, ETH_P_IP);
	/* Number of packets to sniff. */
	packets_to_sniff = atoi(argv[2]) ;

	/* Sniffing. */
	while(packets_to_sniff--){
		/* Got packet successfully. */
		printPacketInHex(packet_buf, len);
		parseEthernetHeader(packet_buf, len);
		parseIpHeader(packet_buf, len);
		parseTcpHeader(packet_buf, len);
	}

	return 0 ;
}

