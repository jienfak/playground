#!/usr/bin/perl
# This script make 'not-formated' code formated.
#

use strict ;
use feature 'say' ;

sub parse {
	my $string = shift @_ ;
	my @strings = split "\n", $string ;
	my $scobs_lvl = shift @_ ;
	for( my $i=0 ; i<@strings ; ++$i ){
		if( $strings[i] =~ /^*.\(\n$/ ){

		}
	}
}
my $PROG_NAME = "code_format" ;

if(@ARGV<2){
	die qq($PROG_NAME: Too few arguments.
	Using: perl code_format.pl [file_in] [file_out]
	) ;
}

my $file_in = $ARGV[0] ;
my $file_out = $ARGV[1] ;

open FILE_IN, "<$file_in" or die "Could not open the file '$file_in': $!" ;
open FILE_OUT, ">$file_out" or die "Could not open the file '$file_out': $!" ;

# Reading all the file.
my $all_the_text = '' ;
while( my $string = <FILE_IN> ){
	$all_the_text .= $string ;
}

$all_the_text =~ s/;/;\n/g ;
$all_the_text =~ s#([\{\(\[])#$1\n#g ;
$all_the_text =~ s#([\}\)\]])#\n$1\n#g ;

my $got_end = 0 ;

print FILE_OUT $all_the_text ;

exit ;
