#!/usr/bin/python3 

import sys

def caesar(string, bias):
    ret_string = ""
    for c in range(0, len(string)) :
        ret_string += str(chr( int(ord(string[c])) + int(bias) ))
    return ret_string

if __name__ == "__main__" :
    program_name = sys.argv[0]
    if len(sys.argv)<2 :
        print(program_name+": Usage - python3 caesar.py [bias] [word1 word2 .. wordn]", file=sys.stderr)
        exit(1)


    bias = sys.argv[1]
    if len(sys.argv)>2 :
        args = sys.argv[2:]
        for string in args :
            print(caesar(string, bias))
            exit()

    string = True
    try:
        while True :
            string = input()
            print(caesar(string, bias))
        exit(0)
    except:
        print(program_name+": we got an exception!", file=sys.stderr)
        exit(0)
