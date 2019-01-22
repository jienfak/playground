#!/usr/bin/python3

import socket
import sys


if __name__ == "__main__" :
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


	host = sys.argv[1]
	port = sys.argv[2]

	s.connect(  (host, int(port) )  )
	

	print("Connected...")
	string = True 
	while string :
		# print("Iteration...")
		string = input() 
		s.send(string.encode())
		data = s.recv(1024)
		print( data.decode()) 

