#!/usr/bin/bash

scripts=$HOME/code/scripts
S=$scripts

# Automaticly gets help.
source $S/sh/sh/modules/helpa.sh

util=$1
shell=$2
pager=$3

tmux set-option remain-on-exit on
tmux split-window
