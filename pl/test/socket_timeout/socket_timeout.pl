#!/usr/bin/perl

my $timeout = ${*$sock}{'io_socket_timeout'} ;
my $before = time () if $timeout;

undef $@;
if(  $sock->connect( pack_sockaddr_in($rport, $raddr) )  ){

}
