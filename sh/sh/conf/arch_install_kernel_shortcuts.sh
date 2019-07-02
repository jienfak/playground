#!/bin/sh

line='kernel.sysrq = 1'
mkdir -p /etc/sysctl.d
if grep "$line" /etc/sysctl.d/99-sysctl.conf ; then
	true
else
	echo "$line" >> /etc/sysctl.d/99-sysctl.conf
fi
