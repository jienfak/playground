#!/usr/bin/tclsh

set PROGRAM_NAME "ping_list"

proc usage {} {
	puts "usage: tclsh ping_list.tcl \[file_of_list\]"
}

if { $::argc < 1 } {
	puts "$PROGRAM_NAME: Not enough arguments"
	usage
	exit
}
# add IP to the file
proc addIp {file ip} {
	set fd [open $file a]
	puts $fd $ip
	close $fd
}

# deletes IP from the file with IPs
proc delIp {file } {
	set fd [open $file r]
	while {![eof $fd]} {
		lappend ipList [gets $fd]
	}
	close $fd

	set fd [open $file w]
	foreach curip $ipList {
		if {$ip ne $curip && curip ne ""} {
			puts $fd $curip
		}
	}
	close $fd
}

# main
set fd [open $argv]
while { ![eof $fd] } {
	set cur_ip [gets $fd]
	open [exec which "ping"] -c 4 $cur_ip
}

exit
