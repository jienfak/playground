#!/usr/bin/env perl
use strict; 
use Socket;
use feature 'say' ;

# Arguments getting.
my $host = $ARGV[0] ;
my $port = $ARGV[1] ;
my $bin_ip = inet_aton($host) ;

socket(SOCK, PF_INET, SOCK_STREAM, getprotobyname('tcp'));
my $paddr = sockaddr_in($port, $bin_ip) ;

connect(SOCK, $paddr) or die "connect:$!\n" ;
my $data;
do{
		my $in = <STDIN> ;
		send SOCK, $in, 0 or die "send: $!" ;

		print $data while ( $data = <SOCK>) ;
}while($data);

say STDERR "$0: exiting program." ;
exit;
