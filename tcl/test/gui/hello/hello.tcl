#!/usr/bin/tclsh
#
package require Tk

button .b -text "Hello, world!"	-command {		\
	puts "You clicked "				\
};
pack .b
