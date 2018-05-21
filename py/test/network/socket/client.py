#!/usr/bin/python3

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect( ( socket.gethostname(), 8008) )
data = sock.recv(1024)
string = data.decode()

print(string)

exit()
