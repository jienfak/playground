#!/usr/bin/python3

import sys
import socket
import time
import argparse
import threading
try:
	from colored import fg, bg, attr
except:
	print("Install 'colored' module with pip.")
	print("Use 'sudo pip3 install colored' for that.")
	exit(4)

# Codes for scan-printing modes.
DEFAULT_MODE = 0
PARSING_MODE = 1

Found_any_opened_port = False

def isPortOpened(host, port):
    scan = False
    while not scan:
        try:
            scan = socket.socket()
        except OSError :
            # Can be opened to many file descriptors.
            continue
    # Time to answer us on needed port.
    scan.settimeout(0.1)
    try:
        scan.connect( (host, port) )
        # If could to connect.
        return True
    except socket.error :
        # Could not connect.
        return False

def printScannedPort(host, port, mode):
	# Getting port status.
	is_opened = isPortOpened(host, port)
	# To show in the terminal.
	is_opened_char = ''
	if is_opened :
		# It's valuable already.
		is_opened_char = '+'
	else:
		is_opened_char = '-'

	# Choosing mode to print.
	if mode == DEFAULT_MODE :
		if is_opened :
			print("["+ fg('green')+is_opened_char+attr('reset') +"] - '"+ host +"' - '"+ str(port) +"' opened!")
		else:
			print("["+ fg('red')+is_opened_char+attr('reset') +"] - '"+ host +"' - '"+ str(port) +"' closed...")
	elif mode == PARSING_MODE:
		print(time.asctime() +":"+ host +":"+ str(port) +":"+ is_opened_char)
	else : raise ValueError("Not any right mode choosed.")

	

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
			Ports to scan in view like '1 2' or '1,2' or '1..80' for ranges.
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
		'-p', "--parsing", action='store_const', dest='print_mode',
		default=DEFAULT_MODE, const=PARSING_MODE,
		help="Output in view to parse, like 'time:host:port:+/-'."
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

	# Ports to scan.
	ports = []
	try:
		for portl in args.ports :
			for portll in portl.split(',') :
				if '..' in portll :
					# Getting port ranges.
					port1, port2 = portll.split('..')	
					for x in range( int(port1), int(port2)+1 ) :
						if not (x in ports) :
							ports.append(int(x))
				elif not (portll in ports) :
					ports.append(int(portll))
	except ValueError :
		print(sys.argv[0] +": Not right port choosed.", file=sys.stderr,)
		exit(7)


	# Getting hosts to scan.
	hosts = []
	for hostl in args.hosts :
		for hostl in args.hosts :
			for hostll in hostl.split(",") :
				if not (hostll in hosts) :
					hosts.append(hostll)

	# Getting print mode.
	print_mode = args.print_mode

	# Getting output.
	if args.output :
		sys.stdout = open(args.output[0], mode='w')

	for port in ports :
		# Scan port for all hosts.
		for host in hosts :	
			# Open thread for one port.
			t = threading.Thread (
				target=printScannedPort,
				args=(host, port, print_mode),
				daemon=True
			)
			t.start()

	# Wait while they scan.
	while threading.activeCount() > 1:
		  time.sleep(1);

if __name__ == "__main__" :
	try:
		main()
		# Success.
		exit(0)
	except KeyboardInterrupt :
		print("\rWe stopped. But why... (Ctrl-C)", file=sys.stderr)
		sys.exit(1)
