#!/usr/bin/perl
#
use strict;
use Socket;
use feature 'say';

my $host = $ARGV[0];
say "Scan host: $host";
my $myhouse = inet_aton($host);

socket(SOCK, PF_INET, SOCK_STREAM, getprotobyname('tcp') );
for(my $i=1 ; $i<0xffff ; ++$i){
	my $paddr = sockaddr_in( $i, $myhouse );

	if( connect(SOCK, $paddr) ){
		say "$i:+"
	}else{
		say "$i:-"
	}
}
exit;
