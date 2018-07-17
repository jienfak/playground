#!/usr/bin/lua

--function declaration
function sum(a, b)
	return a+b
end

-- this function returns 2 values
function vals2(a, b)
	return a, b
end

print( sum(1,5))
print(vals2(1, 5))
