#!/usr/bin/lua

package.path = package.path..";"
	..os.getenv("HOME").."/code/scripts/lua/modules/?.lua"
;

mytable = require("mytable")

t = {1, 2, 3, 4, 5, 6, 7} ;

slice = mytable.slice(t, 3, 4)
print(slice[1])
