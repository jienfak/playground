package RegexGen;

use strict;
use warnings;

sub btwChrsRegex{
	my $word = shift ;
	my $chars= shift ;
	my $regexp = "" ;
	for my $c (split //, $chars){
		$regexp .= "($c$word$c)|" ;
	}
	chop $regexp ;
	return qr/$regexp/ ;
}

1;
