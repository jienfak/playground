#!/usr/bin/awk -f
/(.*)\s+(.*)\s+(.*)\s+(.*)/ {
	print "{'name':'"$1"','phone_number:'"$2"','email':'"$3"','char':'"$4"'}"
	print "Next experssion"
}
