#!/usr/bin/python3

import getopt
import sys

args = sys.argv

optlist, args = getopt.getopt(args, "abc:d")

print(optlist)
