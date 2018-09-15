#!/usr/bin/lua
--[=[

--]=]


print(#arg)
print(arg[1])
for i, el in pairs(arg) do
	print("arg["..i.."] = '"..el.."'")
end
