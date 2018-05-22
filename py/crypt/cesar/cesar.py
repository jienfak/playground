#!/usr/bin/python3

import sys

def crypt_cesar(bias, string):
    buffstr = ''
    for char in string:
        buffstr += chr( ord(char)+bias )
    return buffstr

def uncrypt_cesar(bias, string):
    return crypt_cesar(-bias, string)

args = sys.argv
bias, string = args[1], args[2]

print('uncrypted is "')
print( crypt_cesar(int(bias), string), end='', )
print('"end')

quit()


