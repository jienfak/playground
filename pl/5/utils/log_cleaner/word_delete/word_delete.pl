#!/usr/bin/perl
#
use strict;
use feature 'say';

if(@ARGV != 2){
	say 'Use:';
	say 'perl logclean.pl [source_file] [word]';
	exit
}

my $word = $ARGV[1];

(
	my $dev,	my $ino,	my $mode,	my $nlink,
       	my $uid,	my $rdev,	my $size,	my $atime,
	my $mtime,	my $ctime,	my $blksize,	my $blocks
) = stat $ARGV[0];

open SOURCE, "< $ARGV[0]" or die "open: $!\n";
my @src = <SOURCE>;
close SOURCE;

my @trg, my $i=0;
for my $temp (@src){
	unless( $temp =~ /$word/o ){
		$trg[$i++] = $temp
	}
}

open TARGET, "> $ARGV[0]" or die "open: $!\n";
print TARGET for @trg;
close TARGET;

utime $mtime, $mtime, @ARGV[0];
