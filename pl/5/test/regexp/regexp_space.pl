#!/usr/bin/perl

use feature 'say' ;

$string = "   2  3 3     3		34" ;
say "Without /x";
$string =~ /(  )/ ;
print "'".$1."'\n" ;


say "With /x" ;
$string =~ /(     )/x ;
print "'".$2."'\n" ;
