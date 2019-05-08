extends Label

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Label_mouse_entered():
	self.text = "You are in Label"
	pass # Replace with function body.


func _on_Label_mouse_exited():
	self.text = "You are out  the label"
	pass # Replace with function body.


func _on_Panel_mouse_entered():
	self.text = "You are in the panel"
	pass # Replace with function body.


func _on_Panel_mouse_exited():
	self.text = "You are out the panel"
	pass # Replace with function body.
