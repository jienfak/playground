#!/usr/bin/tclsh

set PROGRAM_NAME "ping_list"

# If not choosed list.
proc usage {} {
	puts "usage: tclsh ping_list.tcl \[file_of_list\]"
}

# Arguments checking.
if { $::argc < 1 } {
	puts "$PROGRAM_NAME: Not enough arguments"
	usage
	exit
}

# Add IP to the file.
proc addIp {file ip} {
	set fd [open $file a]
	puts $fd $ip
	close $fd
}

# Deletes IP from the file with IPs
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

# Main.
set fd [open $argv]

# Read and ping while isn't end of file.
while { ![eof $fd] } {
	set cur_ip [gets $fd]
	if {$cur_ip ne ""} {
		# Try to ping and print error if got it.
		if { [catch { set re [exec ping $cur_ip -c 4] } err_msg ] } {
				puts $err_msg
		} else {
			# If could ping it print output.
			puts $re
		}
	}
}

exit
