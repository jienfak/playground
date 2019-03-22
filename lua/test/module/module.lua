#!/usr/bin/lua

-- Object of module to return.
local Module = {}
-- Function of module definition.
function Module.foo()
	print "I'm in Module.foo!"
end
-- Require gets it via "require".
return Module
