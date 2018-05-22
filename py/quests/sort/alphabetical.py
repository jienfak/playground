#!/usr/bin/python3
words = str(input('Enter your words:'));

l = words.split(', ');
l.sort();
for x in l:
    print(x, end=', ');
exit();
