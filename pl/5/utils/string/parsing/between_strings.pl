#!/usr/bin/perl
# This program finds text between 2 lines.

use strict;
use feature "say" ;

if(@ARGV<2){
	exit do{
		say "$0: Not enough arguments.";
		say "Usage: perl between.pl [string1] [string2]";
		return 1 ;
	} ;
}

my $start = $ARGV[0] ;
my $end   = $ARGV[1] ;

my @lines = <STDIN> ;
my $lines = join("\n", @lines) ;

$lines =~ m#$start(.*?)$end#m ;
print $1.$2.$3 ;
