#!/usr/bin/perl
#
use Net::PcapUtils;
use NetPacket::Ethernet qw(:strip);
use NetPacket::IP qw(:strip);
use NetPacket::TCP;

sub process_pkt{
	my ($arg, $hdr, $pkt) = @_;
	my $tcpobj = NetPacket::TCP->decode(
	      	ip_strip( eth_strip($pkt) )  
	);
	if( ($tcpobj->{src_port}==110) or ($tcpobj->{dest_port} == 110) ){
		print $tcp_obj->{data};
	}
}

Net::PcapUtils::loop(\&process_pkt, FILTER=>'tcp');
