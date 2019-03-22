#!/usr/bin/lua

t = {}
table.insert(t, 2134)
for key, word in pairs(t) do
	print(key, word)
end

t["hcat"] = {}
table.insert(t["hcat"], {1234} )
for key, word in pairs(t) do
	print(key, word)
end
