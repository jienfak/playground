#!/usr/bin/perl
#
use feature 'say' ;

my @arr ;

# Pushing scalar
push @arr, 0 ;
# Pushing list
push @arr, (1, 2, 3);

for $x (@arr){
	say $x;
}

exit;
