#!/usr/bin/perl
#
use strict;
use Socket;
use feature 'say';

my $host = $ARGV[0];
say "Scan host: $host";
my $myhouse = inet_aton($host);
for(my $i=1 ; $i<65000 ; ++$i){
	socket(SOCK, PF_INET, SOCK_STREAM, getprotobyname('tcp') );
	my $paddr = sockaddr_in( $i, $myhouse );

	if( connect(SOCK, $paddr) ){
		close SOCK;
		say "$i:+";
	}else{
		say "$i:-";
	}
}
exit;
