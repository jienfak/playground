#!/usr/bin/python3

import sys
import threading
import socket
import time
from termcolor import colored 

def scan_port(host, port):
    scan = socket.socket()
    scan.settimeout(0.1)
    try:
        scan.connect( (host, port) )
    except socket.error:
        return False
    else:
        return True


ports = [20, 21, 22, 23, 42, 43, 53, 67, 69, 80, 443]
host = sys.argv[1]

for port in ports:
    if scan_port(host, port):
        print(port)

exit()
