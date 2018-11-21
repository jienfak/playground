#!/usr/bin/python3

import sys
import socket
import time
import argparse

def scanPort(host, port):
    scan = socket.socket()
    scan.settimeout(0.1)
    try:
        scan.connect( (host, port) )
    except socket.error:
        return False
    else:
        return True

def makeParser() :
	arg_parser = argparse.ArgumentParser (description=
	"Scans ports you choosed."
	)

	arg_parser.add_argument(
		"-P", "--ports",
		nargs="+",
		help="""Ports to scan in view like '1,2,3 34,5 21'.
		Default ports are 20, 21, 22, 23, 42, 43, 53, 67, 69, 80, 443.
		D"""
	)
	arg_parser.add_argument(
		'-H', "--hosts",
		required=True,
		nargs="+",
		help="Hosts to scan ports in view like  '1.1.1.1,123.123.123.123 google.com '"
	)
	arg_parser.add_argument(
		'-t', "--parse-form",
		help="Output in view to parse, like 'host:port:+/-'."
	)


	return arg_parser

def main():

	arg_parser = makeParser() 
	args = arg_parser.parse_args()

	# Ports to scan if no any choosed.
	ports = [20, 21, 22, 23, 42, 43, 53, 67, 69, 80, 443]
	if args.ports :
		ports = []
		for portl in args.ports :
			for portll in portl.split(",") :
				if not (portll in ports) :
					ports.append(int(portll))

	# print(ports)

		

	# Getting hosts to scan.
	hosts = []
	for hostl in args.hosts :
		for hostl in args.hosts :
			for hostll in hostl.split(",") :
				if not (hostll in hosts) :
					hosts.append(hostll)
	# print(hosts)

	for host in hosts :
		print("-"*50)
		for port in ports:
			if scanPort(host, port):
				print("[+] '"+ host +"' - '"+ str(port) +"' port opened.")
			else:
				print("[-] '"+ host +"' - '"+ str(port) +"' port closed.")


if __name__ == "__main__" :
	main()
