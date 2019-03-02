import ctypes
lib = ctypes.cdll.LoadLibrary("./liblib.so")

class Foo(object):
	def __init__(self):
		self.obj = lib.Foo_new()

	def bar(self):
		lib.Foo_bar(self.obj)

f = Foo()
f.bar()
