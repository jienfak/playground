#!/usr/bin/lua

package.path = package.path..";"..
	os.getenv("HOME").."/code/scripts/lua/modules/?.lua"
;

local mytable = require("mytable")

t = {
		1, 2, 3,
		{
			"abdcdf"
		}
	}
;

mytable.printStruct(t)
