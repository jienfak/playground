#!/usr/bin/python3

import sys
import socket
import time
import argparse
import threading

# Codes for scan-printing modes.
DEFAULT_MODE = 0
PARSING_MODE = 1

def isPortOpened(host, port):
    scan = socket.socket()
    scan.settimeout(0.1)
    try:
        scan.connect( (host, port) )
    except socket.error:
        return False
    else:
        return True

def printScannedPort(host, port, mode):
	# Choosing mode to print.
	if mode == DEFAULT_MODE :
		if isPortOpened(host, port) :
			print("[+] - '"+ host +"' - '"+ str(port) +"' opened.")
		else:
			print("[-] - '"+ host +"' - '"+ str(port) +"' closed.")
	elif mode == PARSING_MODE:
		is_opened = '+'
		if isPortOpened(host, port) :
			# It's valuable already.
			pass
		else:
			is_opened = '-'
		print(time.asctime() +":"+ host +":"+ str(port) +":"+ is_opened)
	

def makeParser() :
	arg_parser = argparse.ArgumentParser (description=
	"Scans ports you choosed."
	)

	arg_parser.add_argument(
		"-P", "--ports",
		nargs="+",
		# Most usable ports by default.
			default = ['20', '21', '22', '23', '42', '43', '53', '67', '69', '80', '443'] ,
		help=(
			"""
			Ports to scan in view like '1,2,3 34,5 21'.
			Default ports are 20, 21, 22, 23, 42, 43, 53, 67, 69, 80, 443.
			"""
		)
	)
	arg_parser.add_argument(
		'-H', "--hosts",
		required=True,
		nargs="+",
		help="Hosts to scan ports in view like  '1.1.1.1,123.123.123.123 google.com '"
	)
	arg_parser.add_argument(
		'-t', "--for_parsing", action='store_const', dest='parsing',
		default=DEFAULT_MODE, const=PARSING_MODE,
		help="Output in view to parse, like 'host:port:+/-'."
	)
	arg_parser.add_argument(
		'-o', "--output",
		nargs=1,
		default=False,
		help="File output."
	)


	return arg_parser


def main():
	arg_parser = makeParser() 
	args = arg_parser.parse_args()

	# Ports to scan if no any choosed.
	ports = []
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

	# Getting print mode.
	print_mode = args.parsing

	# Getting output.
	if args.output :
		sys.stdout = open(args.output[0], mode='w')

	for host in hosts :
		for port in ports :
			t = threading.Thread (
				target=printScannedPort,
				args=(host, port, print_mode)
			)
			t.start()



if __name__ == "__main__" :
	main()
