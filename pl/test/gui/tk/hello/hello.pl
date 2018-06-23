#!/usr/bin/perl
#

use Tkx;

Tkx::button(
	".b",
	-text => "Hello, World!",
	-command => sub { Tkx::destroy("."); },
);
Tkx::pack(".b");
Tkx::MainLoop();

