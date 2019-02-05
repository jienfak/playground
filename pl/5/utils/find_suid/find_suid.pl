#!/usr/bin/perl
#
use strict;
use Cwd;
use feature 'say';

sub Findf {
	my ($work) = shift;
	my ($start)= &cwd;
	chdir($work) or die "chdir: $!";
	opendir DIR, $work;
	my @names = readdir(DIR) or die "readdir: $!";
	closedir(DIR);

	foreach my $name (@names){
		next if($name eq '.');
		next if($name eq '..');
		say $name ;

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

if(@ARGV < 1){
	say 'find_suid: Too few arguments.';
	say 'Using: perl find_suid.pl [start_dir]';
	exit
}

&Findf($ARGV[0]);


