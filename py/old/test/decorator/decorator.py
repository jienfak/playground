#!/usr/bin/python3

def anotherFunc(func):
	def otherFunc():
		val = "Result from %s is %s" % (func(), eval(func()))
		return val
	return otherFunc

@anotherFunc
def aFunc():
	return "1+1"

if __name__ == "__main__" :
	value = aFunc()
	print(value)
