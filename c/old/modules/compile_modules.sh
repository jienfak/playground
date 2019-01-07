#!/usr/bin/sh
cd src
for var in *.c 
do
	cc -o ../lib/$var.so -c $var
done
