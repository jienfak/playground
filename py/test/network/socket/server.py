#!/usr/bin/python3

import socket

print("Server starting...")
print("Creating listening socket...")
listen = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
print("Binding socket...")
listen.bind( (socket.gethostname(), 8008) )


while True:
    print("Listening for connections...")
    listen.listen(5)
    (sock, addr) = listen.accept()
    print("Connection From: '"+str(addr)+"'" )
    sock.send( "Hello, World!\n".encode() )
    sock.close()
