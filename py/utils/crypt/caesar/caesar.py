#!/usr/bin/python3 

import sys

def caesar(string, bias):
    ret_string = ""
    for c in range(0, len(string)) :
        ret_string += chr( ord(string[c]) + bias )
    return ret_string

if __name__ == "__main__" :
    bias = sys.argv[1]
    if len(sys.argv)>2 :
        args = sys.argv[1:]
        for string in args :
            print(caesar(string, bias))
            exit()

    string = True
    try:
        while string :
            string = input()
            print(caesar(string, bias))
    except:
        exit(1)
        pass

    exit()
