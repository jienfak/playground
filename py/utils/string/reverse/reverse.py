#!/usr/bin/python3

import sys

if __name__ == "__main__" :
    pname = sys.argv[0] 

    if len(sys.argv)>=2 :
        args  = sys.argv[1:]

        for string in args :
            print(string[::-1])

        exit(0)

    string = True
    try:
        while string :
            string = input()
            print(string[::-1])
    except KeyboardInterrupt :
        print(pname+": got KeyboardInterrupt.", file=sys.stderr)
    except EOFError :
        print(pname+": got EOFError.", file=sys.stderr)

    exit(0)
