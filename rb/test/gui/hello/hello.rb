#!/usr/bin/ruby-2.3

require 'tk'
root = TkRoot.new {
	title "Hello, World!"; padx 50; pady 15
}

#one label
TkLabel.new(root) {
	text "Hello, Wordl!"
	pack { padx 100; pady 100; side "left" }
}

#other label 
TkLabel.new(root) {
	text "Other label, you knowl."
	pack { padx 200; pady 200; side "right" }
}

#button 
but = TkButton.new(root) {
	text "Click me, Idiot!"
	pack { padx 300; pady 300; side "left" }
}
but.bind("Enter", proc { but.text "Welcome!"	})
but.bind("Leave", proc { but.text "Bye!"	})

#other button 
oth_but = TkButton.new(root) {
	text "I'm an other button!"
	pack {padx 300; pady 300; side "right"}
}
oth_but.bind("Press", proc { but.text "You clicked not me!" });
Tk.mainloop
