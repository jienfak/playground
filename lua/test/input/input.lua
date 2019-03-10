#!/usr/bin/lua

local answer
repeat
	io.write("Continue with this operation?(y/n)")
	io.flush()
	answer=io.read()
until answer=='y' or answer=='n'

print(answer)


