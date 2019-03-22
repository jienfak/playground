#!/usr/bin/lua

local Module = {} ;

function Module.split(input_str, sep)
	if sep == nil then
		sep = "%s" ;
	end
	local t={} ;
	for str in string.gmatch(input_str, "([^"..sep.."]+)") do
		table.insert(t, str)
	end
	return t
end

--[[
-- Test
t = Module.split("string string1 string2 suck1 suck2")
for _, string in pairs(t) do
	print(string)
end
--]]

return Module
