#!/bin/sh

source ~/.profile
source $SHMODS/chores/hasprog.sh

if hasprog tmux ; then
	tmux
fi

eval $SHELL
