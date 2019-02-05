#!/usr/bin/perl
#
use feature 'say';

@arr = ('zero', 'one', 'two', 'three') ;

say 'Before shifting...';
for $x (@arr){
	say $x;
}

while(@arr){
	$var = shift @arr ;
	say "After shifting of '$var'...";
	for $x (@arr){
		say $x;
	}
}

exit;
