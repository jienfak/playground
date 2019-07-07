#!/bin/sh

source ~/.profile
source $SHMODS/chores/hasprog.sh
source $SHMODS/interactive/ask.sh

if hasprog tmux ; then
	tmux;
	exit
fi

if ask "I could not start 'tmux'. Should I start 'screen'?[yn] " ; then
	screen
	exit
fi

eval $SHELL
