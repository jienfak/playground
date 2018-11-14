#!/usr/bin/python3

import sys
import socket
import time

def scan_port(host, port):
    scan = socket.socket()
    scan.settimeout(0.1)
    try:
        scan.connect( (host, port) )
    except socket.error:
        return False
    else:
        return True


if __name__ == "__main__" :
	ports = [20, 21, 22, 23, 42, 43, 53, 67, 69, 80, 443]
	host = sys.argv[1]

	for port in ports:
		if scan_port(host, port):
			print(port)
	exit()
