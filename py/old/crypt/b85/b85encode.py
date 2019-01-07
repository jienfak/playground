#!/usr/bin/python3

import sys
import base64

byte = bytes(sys.argv[1], "utf-8")

print(str(base64.b85encode(byte)))

exit()
