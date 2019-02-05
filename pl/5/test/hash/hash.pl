#!/usr/bin/perl
#
use feature 'say' ;

%hash = (
	key => 'value',
	other_key => 'other_value'
) ;

say $hash{key};
say $hash{other_key};

exit;
