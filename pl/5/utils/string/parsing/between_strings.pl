#!/usr/bin/perl

use strict;
use feature "say" ;

if(@ARGV<2){
	exit do{
		say "$0: Not enough arguments.";
		return 1 ;
	} ;
}

my $start = $ARGV[0] ;
my $end   = $ARGV[1] ;

my $string;

until( ($string=<STDIN>) =~ m/$start(.*)/g){}
$string =~ m/$start(.*)/ ;
say $1 ;
until( ($string=<STDIN>) =~ m/(.*)$end/){
	print $string ;
}
$string =~ m/(.*)$end/ ;
print "$1" ;
