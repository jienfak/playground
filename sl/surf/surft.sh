#!/bin/sh
# Simply lets you run surf being tabbed.

MAX_SURF_WINDOWS=100

# Find next xid file to use.
for i in $(seq $MAX_SURF_WINDOWS) ; do
	curfile="$HOME/.surf/tabbed-surf.$i.xid"
	if [ ! -f  "$curfile" ] ; then
		xidfile="$curfile"
		break
	fi
done

uri=""

if [ "$#" -gt 0 ];
then
	uri="$1"
fi

runtabbed() {
	tabbed -dn tabbed-surf -r 2 surf -e '' "$uri" >"$xidfile" \
		2>/dev/null &
}

if [ ! -r "$xidfile" ];
then
	runtabbed
else
	xid=$(cat "$xidfile")
	xprop -id "$xid" >/dev/null 2>&1
	if [ $? -gt 0 ];
	then
		runtabbed
	else
		surf -e "$xid" "$uri" >/dev/null 2>&1 
		rm $xidfile
	fi
fi

