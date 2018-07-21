#!/usr/bin/lua

-- it's a loop

for i=2 , 10, 2 do
	print(i)
end

i = 1
while i<10 do
	i = i + 1
	print(i)
end

o = {
	a=1, b=2, c=3,
	d=4, e=5, f=6,
	g=7, k=8, o=9
}

print "Before"

for key, value in pairs(o) do
	print("o["..key.."]=".."'"..value.."'")
end
