#/usr/bin/python3

class human:
   def __init__(self, age=None, fullname='Unknown Unknown'):
        self.fullname=fullname
        self.age=age
        print('Human', self.fullname, ', age', self.age, 'was created')

Human = human()
exit()
