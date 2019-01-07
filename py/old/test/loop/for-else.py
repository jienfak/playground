#!/usr/bin/python3

arr = (0, 1, 2, 3, 4, 5, 6)

print("Here break won't work!")
for x in arr :
    print(x)
    if x==7 :
        break
else: #I get here if do not break a cycle
    print("I'm in else block!")

print("Here it will work!")
arr += (7,)
for x in arr :
    print(x)
    if x==7 :
        break
else: #I won't get here because of break
    print("I'm in else block!")
