#!/usr/bin/perl

use feature 'say' ;

# $_ - one of standard vars
# @_ - one of standard arrays

@_ = (0, 1, 2, 3, 4) ;

say 'Before shifting...';
for $x (@_){
	say  $x;
}

say 'After shifting...';
$var = shift ;
for $x (@_){
	say $x;
}

say 'After popping...';
$var = pop ;
for $x (@_){
	say $x;
}
