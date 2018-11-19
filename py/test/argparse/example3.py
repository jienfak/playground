#!/usr/bin/python3

import argparse

parser = argparse.ArgumentParser()

parser.add_argument("-1", "--one", nargs="*", help="This will be option one")

print(parser.parse_args())

res = parser.parse_args()

for i in res.one :
	print(i)
