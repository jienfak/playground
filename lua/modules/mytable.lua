#!/usr/bin/lua

local Module = {}

function Module.len(t)
	-- Returns length of table.
	local i
	for _ in pairs(t) do i = count + 1 end
	return i
end

function Module.slice(tbl, first, last, step)
	local sliced = {}

	for i=(first or 1), last or #tbl, step or 1 do
		sliced[#sliced+1] = tbl[i]
	end

	return sliced
end

function Module.printStruct(t, n)
	--[[if not ( type(t) == "table" )then
		return
	end
	--]]
	local tab = n or 0
	for key, word in pairs(t) do
		print(string.rep("\t", tab), tostring(key)..":"..tostring(word))
		if type(word) == "table" then
			Module.printStruct(word, tab + 1)
		end
	end
end

return Module
