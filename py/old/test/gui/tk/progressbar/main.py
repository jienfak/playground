#!/usr/bin/env python3

import tkinter as tk
from tkinter import ttk

def progress(current_value):
	progress_bar["value"]=current_value

max_value = 100

prorgess_bar = ttk.Progressbar(master, orient="horizontal", length=300, mode="determinate")
progress_bar.pack(side=tk.TOP)
current_value=0
progress_bar["value"] = current_value
progress_bar["maximum"]=max_value

divisions=10

for i in range(divisions):
	current_value += 10
	progress_bar.after(500, progress(current_value))
	progress_bar.update() # Update of GUI.

