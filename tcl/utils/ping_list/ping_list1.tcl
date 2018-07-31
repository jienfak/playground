#!/usr/bin/tclsh
#

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
set fd [open ]
