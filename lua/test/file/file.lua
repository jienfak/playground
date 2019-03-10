#!/usr/bin/lua

-- Example showing how file input/output works.

-- Opening and getting iterator to read lines.
lines = io.lines(arg[1])

-- Open file.
local file = io.open(arg[2], "w")
-- Writting all the lines of file.
for line in lines do
	file:write(line.."\n")
end

-- Exiting.
os.exit()
