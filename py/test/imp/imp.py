#!/usr/bin/python3

class Tree(object):
    def __init__(self, kind, height):
        self.kind = kind
        self.age = 0
        self.height = height

    def info(self):
        #tree info
        print("{} years old {}, {} meters high.".format(self.age, self.kind, self.height) )

    def grow(self):
        #grow method
        self.age += 1
        self.height += 0.5

class FruitTree(Tree):
    def __init__(self, kind, height):
        super().__init__(kind, height)

    def give_fruits(self):
        print("Collected 20kg of {}s".format(self.kind))



tree_1 = Tree("oak", 0.5)
tree_1.info()
tree_1.grow()
tree_1.info()

tree_2 = FruitTree("apple", 0.7)
#acces to methos of super-class
tree_2.info()
tree_2.grow()
#use our method
tree_2.give_fruits()
#Super-class object can't use these methods
# tree_1.give_fruits() //error
