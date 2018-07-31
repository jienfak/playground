#!/usr/bin/tclsh
if { $::argc > 0 } {
	set i 1
	foreach arg $::argv {
	puts "argv\[$i\] = $arg"
		incr i
	}
} else {
	puts "argv.tcl: Arguments not found!"
}
