#!/usr/bin/python3

import sys;
if len(sys.argv)<2:
    print(sys.argv[0]+': Too few arguments.')
    exit()

words = str(sys.argv[1])

l = words.split(', ')
l.sort()

for x in l:
    print(x, end=', ')

exit()
