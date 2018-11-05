#!/usr/bin/python3

import socket
import sys

s = socket.socket()

host = sys.argv[1]
port = sys.argv[2]

s.connect(host, port)

while True :
    string = input()
    s.send(data.encode())
