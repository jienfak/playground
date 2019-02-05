#!/usr/bin/perl
#

use feature 'say' ;

@arr = (0, 1, 2, 3) ;

say 'Before incrementing...';
foreach $x (@arr){
	say $x;
}
# It changes values of array, because
# $x - variable you use.
foreach $x (@arr){
	++$x
}

say 'After incrementing...';
foreach $x (@arr){
	say $x;
}

exit; 
