#!/usr/bin/perl
#
use feature 'say' ;

@arr = (0, 1, 2, 3, 4, 5) ;

say 'Before any poping...';
for $x (@arr){
	say $x;
}

say 'Poping...';
for $x (@arr){
	$var = pop @arr ;
	say "After poping $var...";
	for $y (@arr){
		say $y;
	}
}

exit;
