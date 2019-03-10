#!/usr/bin/lua

-- Example to show how arguments getting works.
-- Arguments are in 'arg' table.

for key, i in pairs(arg) do
	print("arg["..key.."]='"..i.."'")
end
