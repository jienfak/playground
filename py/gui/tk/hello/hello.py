#!/usr/bin/python3

import tkinter

#handlers
def button_clicked():
    print ("Hello, World!")

root = tkinter.Tk ()

button = tkinter.Button (
        root,
        bg="red",
        text="It's clickable, really!",
        command=button_clicked
)
button.pack()


#it must be in the end
root.mainloop()
