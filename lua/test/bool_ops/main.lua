#!/usr/bin/lua

print("25 and 26 = "..tostring(25 and 26))
print("false and 26 = "..tostring(false and 26))
print("25 and false = "..tostring(25 and false))
print("false and false = "..tostring(false and false))

print()

print("25 or 26 = "..tostring(25 or 26))
print("25 or false = "..tostring(25 or false))
print("false or 26 = "..tostring(false or 26))
print("false or false = "..tostring(false or false))

print()

print("not 26 = "..tostring(not 26))
print("not false = "..tostring(not false))

return
