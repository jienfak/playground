#!/usr/bin/bash

scripts=$HOME/code/scripts

util=$1
shell=$2
pager=$3

eval "$util" | $pager
eval "$util -h" | $pager
eval "$util --help" | $pager
$shell

