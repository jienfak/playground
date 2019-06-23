#!/usr/bin/perl
# * This script decryptes written by faklog log.	*
# * Using: perl decrypt.pl [log] [keycodes] [outfile]	*
#
use strict;
use feature 'say';
my $progname = "uncrypt-log";

if(@ARGV < 3){
	die say "$progname: Too few arguments(perl decrypt-log.pl -h)"
}

if($ARGV[0]=='-h'){
	die say "using: perl decrypt-log.pl [log] [keycodes] [outfile]"
}


open FILE, $ARGV[0];
my @data = <FILE>;
close FILE;
my $buff = do{
	my $string = '';
	for my $x (@data){
		$string.=$x;
	}
	$string
};
my @lines = split "\n", $buff;

#getting names of buttons
open FILE, $ARGV[1];
@data = <FILE>;
close FILE;
$buff = do{
	my $string = '';
	for my $x (@data){
		$string.=$x;
	}
	$string
};
my @buttons = split "\n", $buff;

open FILE, ">",$ARGV[2];
foreach my $line (@lines){
	$line =~ /^(\d+)\|(.*)$/;
	my $butt = $buttons[ int($1)-1 ];
	print FILE "'$butt'|$2\n"
}
close FILE;

exit;

