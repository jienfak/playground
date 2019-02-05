#!/usr/bin/perl
#
use strict;
use feature 'say';

opendir DIR, '.';
my @dirs = readdir(DIR);
print foreach @dirs, ' ' ;
