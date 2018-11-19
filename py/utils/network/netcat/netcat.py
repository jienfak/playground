#!/usr/bin/python3

import socket
import sys


if __name__ == "__main__" :
	s = socket.socket()


	host = sys.argv[1]
	port = sys.argv[2]

	s.connect(  (host, int(port) )  )

	while True :
		string = input()
		s.send(string.encode())
		data = s.recv(1024)
		print("'"+ data.decode() +"'") 

