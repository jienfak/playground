#!/usr/bin/perl
#
use strict;
use Cwd;
use feature 'say';

sub Findf
{
	my ($work) = shift;
	my ($start)= &cwd;
	chdir($work) or die "Error!:changing dir\n";
	my @names = readdir(DIR) or die "Error!:reading dir\n";
	closedir(DIR);

	foreach my $name (@names){
		next if($name eq '.');
		next if($name eq '..');

		if(-l $name){ next; }

		if(-d $name ){
			Findf($name);
			next;
		}

		if(-u $name){
			say $name;
		}
		chdir $start;
	}
}

say "dir = $ARGV[0]";
&Findf($ARGV[0]);


