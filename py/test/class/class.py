#/usr/bin/python3

class Human:
    #static variable
    _obj_count = 0

    def getCount():
        return Human._obj_count 

    #initialization
    def __init__(self, age=None, fullname='Unknown Unknown'):
        self.fullname=fullname
        self.age=age
        print('Human', self.fullname, ', age', self.age, 'was created')
        Human._obj_count += 1

    #methods of objects
    def say(self, phrase):
        print(self.fullname+": "+phrase);

    def act(self, action):
        print("* "+self.fullname+" "+action+" *")

human = Human()
human.act("sucks dick")
human.say("It's so tasty!")

coup = Human(fullname="Sucker Motherfucker", age=1), Human(), Human()
print(str(Human.getCount()) + " objects are created now")

exit()
