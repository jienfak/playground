#!/usr/bin/env sh

for file in ${@:2} ; do
	echo $file
	grep -i $1 $file
done
