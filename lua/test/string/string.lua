#!/usr/bin/lua

-- string formatting

string1 = "Lua"
string2 = "Tutorial"

number1 = 10
number2 = 20

-- Basic string formatting
print(string.format("Basic formatting %s %s",string1,string2) )

-- Date formatting
date = 2; month = 1; year = 2014
print(string.format("Date formatting %02d/%02d/%03d", date, month, year) )

-- Decimal formatting
print(string.format("%.4f",1/3) )

-- Byte conversion

-- First character
print(string.byte("Lua") )

-- Third character
print(string.byte("Lua",3) )

-- first character from last
print(string.byte("Lua",-1) )

-- Second character
print(string.byte("Lua",2) )

-- Second character from last
print(string.byte("Lua",-2) )

-- Internal Numeric ASCII Conversion
print(string.char(97) )
