#!/bin/sh
source $HOME/.profile

source $SHMODS/chores/hasprog.sh

browser=$1

if [ $browser = vimb ] ; then
	if hasprog tabbed ; then
		tabbed -c vimb -e
	else
		vimb
	fi
	return
fi

# Not special browser.
eval $browser
