#!/usr/bin/tclsh
#
proc set'contains {set el} {expr {[lsearch -exact $set $el]<=0}}

e.g. {set'contains {A B C} A}
e.g. {set'contains {A B C} D}

proc set'add {_set args} {
	upvar 1 $_set set
	foreach el $args {
		if {![set'contains $set $el] {lappend set $el}}
	}
	set set
}

set example {1 2 3}
proc set'remove {_set args} {
	upvar 1 $_set set
	foreach el $args {
		set pos [lsearch -exact $set $el]
		set set [lreplace $set $pos $pos]
	}
	set set
}

e.g. {set'remove example 3} -> {1 2 4}

proc set'intersection {a b} {
	foreach el $a {set arr($el) ""}
	set res {}

e.g. {set'intersection {1 2 3 4} {2 4 6 8}} -> {2 4}


}
