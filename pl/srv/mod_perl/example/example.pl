#!/usr/bin/perl

use strict ;
use warnings ;

my $request = shift ;
$request->content_type('text/html');

$_ = $request->unparsed_uri() ;

$_ =~ /(.*)\?(.*)/ ;

my @ARGS =  split /{0}\\\&/, $2 ;
my %ARGS;
for my $x (@ARGS){
	$x =~ /(\w+){0}\\=(\w+)/ ;
	$request->print("$x='#$1#=#$2#'<br>");
	$ARGS{$1} = $2 ;
}

$request->print(qq{
<html>
	<head>
		<title> This is a title! </title>
	</head>
	<body>
		Here is a body!<br>
		Request is '<b>$request->unparsed_uri() </b>',<br>
	</body>
</html>
});


exit;
