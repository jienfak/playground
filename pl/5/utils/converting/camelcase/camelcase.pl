#!/usr/bin/perl

my $text = <STDIN> ;
$text = join(  '', map( ucfirst, split(/[^a-z]*/, lc $text) )  ) ;
print $text, "\n";
