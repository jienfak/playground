#!/usr/bin/perl
# Program for pasring URL.
use strict ;
use feature 'say' ;

if( @ARGV<1 ){
	die \
qq!Usage1: perl url_json_parser.pl [expression]
Usage2(To print not human-readable view.): perl url_json_parser.pl [expression] -n
!;
}

my $string = $ARGV[0] ;
$string =~ /((\w+)\:\/\/)?(\w+\.\w+)((\:(\d+))?\/((\w+\/?)*)?(\??(.*)))?/ ;

=begin comment
	say $1 ;
	say $2 ;
	say $3 ;
	say $4 ;
	say $5 ;
	say $6 ;
	say $7 ;
	say $8 ;
	say $9 ;
	say $10 ;
=end comment
=cut

my $proto    = $2 ;
my $port     = $6 ;
my $hostname = $3 ;
my $args     = $10 ;
my $query    = '/'.$7 ;

my @pairs = split /\\{0}\&/, $args ;


=begin comment
for my $x (@pairs){
	say $x ;
}
=end comment
=cut

my $formed_args = '' ;
for my $x (@pairs){
	$x =~ /^(.*)\\{0}=(.*)$/ ;
	$formed_args .= qq!\t\t$1: $2\n! ;
}


my $json_uri = qq!{
	"protocol": "$proto",
	"hostname": "$hostname",
	"port": $port
	"query": "$query",
	"arguments": {
		$formed_args
	}
}
! ;

if($ARGV[1] && $ARGV[1]=="-n"){
	$json_uri =~ s/\s//g 
}

print $json_uri;
exit;

