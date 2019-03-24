#!/usr/bin/perl
#
# Simple script getting list of tools for Blackarch(18 March 2019).

use strict;
use warnings;
use feature 'say';

my $url = 'https://blackarch.org/tools.html';
my $data = `wget --output-document=- $url` ;

# Chores about regexps.
my $mark = qr/'|\""/ ;

# Categories.
my @hcats = () ;
while( $data =~ m{
			<.*a.*class=$mark?hcat$mark?.*>(.*)</a>
		}gx
	){
	#say $1 ;
	my $hcat = $1 ;
	$hcat =~ s/blackarch-?//g ;
	push @hcats, $hcat ;
}

# Utils.
my @utils = () ;
while( $data =~ m{
		<.*td.*class=$mark?tbl-name$mark?.*>(.*)</td>
	}gx
	){
	#say $1;
	push @utils, $1 ;
}

# For chomp.
$/ = ' ' ;
for(my $i=0 ; $i<@utils ; ++$i ){
	my $string = $utils[$i]." ".$hcats[$i] ;
	chomp $string;
	say $string ;
}
# Back start chomp function.
$/ = '\n' ;

exit;
