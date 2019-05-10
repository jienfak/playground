#!/usr/bin/env perl
#
# Gets URLS from HTML-like links from standard input.

use RegexGen;
use strict;
use feature 'say';



my @lines = <STDIN> ;
my $data  = join "", @lines ;

my $prefixes_regex = qr{(href)|(src)}; 
my $quotes_regex   = RegexGen::btwChrsRegex(".*", "'\"`") ;

while( $data =~ m{ ($prefixes_regex=( $quotes_regex | (\w+) )  )}ixg){
	say $4;
}

exit;
