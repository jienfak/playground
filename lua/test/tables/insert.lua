#!/usr/bin/lua

t = {}
table.insert(t, 1)
table.insert(t, 56)

for key, word in pairs(t) do
	print(key, word)
end
