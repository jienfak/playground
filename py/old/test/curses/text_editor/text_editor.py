#!/usr/bin/python3

def __init__(self, file):
        self.file = file
        self.scr = curses.initscr()
        self.scr.border()
        self.scr_height, self.scr_width = self.scr.getmaxyx()
        self.text_win = curses.newwin(self.scr_height - 1, self.scr_width, 1, 0)
        self.file_text = file.content
        if self.file_text != None:
            self.text_win.addstr(self.file_text)
        curses.noecho()
        #curses.start_color()
        #curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_GREEN)

        if self.file.exists:
            self.start_editor()
        else:
            curses.endwin()
            gc.error('An error occurred while editing this file.') 
