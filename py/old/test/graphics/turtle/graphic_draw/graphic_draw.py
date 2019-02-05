#!/usr/bin/python3

import turtle

k = 2.5
matrix_size = 32 * k

while True :
    turtle.reset()
    formula = input("Enter formula: y(x) = ")
    x = float(-matrix_size)
    
    turtle.goto(-matrix_size, 0)
    while x<matrix_size :
        turtle.down()
        try:
            x += 0.5
            turtle.setpos(x*k, eval(formula)*k)
        except ZeroDivisionError :
            continue
        turtle.up()
        
    input()
    

"""
    turtle.down()
    turtle.forward(35)
    turtle.left(55)
    turtle.up()
    turtle.forward(30)


    turtle.goto(100,150)
    turtle.down()
    turtle.color("red")
    turtle.circle(100)
    turtle.mainloop()
"""
