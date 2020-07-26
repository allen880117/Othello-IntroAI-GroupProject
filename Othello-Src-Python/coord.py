#!/usr/bin/env python3


class Coord():
    """ Class: Coord """

    def __init__(self, *args):
        if(len(args) == 0):
            self.x = -1
            self.y = -1
        elif(len(args) == 2):
            self.x = args[0]
            self.y = args[1]
        else:
            raise BaseException("Number of Argument for Coord is Wrong")

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

    def __add__(self, rhs):
        return Coord(self.x+rhs.x, self.y+rhs.y)
    
    def __eq__(self, rhs):
        return (self.x == rhs.x and self.y == rhs.y)

    def __ne__(self, rhs):
        return not (self.x == rhs.x and self.y == rhs.y)

NO_ACTION = Coord(-1, -1)
direction = [Coord(-1, -1), Coord(-1, 0), Coord(-1, 1), Coord(0, -1),
             Coord(0, 1),   Coord(1, -1), Coord(1, 0),  Coord(1, 1)]
