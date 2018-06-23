#!/usr/bin/tclsh
#
package require Tk

button .b			\
	-text "Hello, world!"	\
	-command {destroy .}
pack .b
