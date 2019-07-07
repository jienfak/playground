#!/bin/sh sh

for file in ${@:2} ; do
	echo $file":"
	grep -in "$1" "$file"
done
