#!/usr/bin/env python3
import board as board
import coord as coord
import uct as uct


class Player():
    def __init__(self, **kwargs):
        """ Constructor """
        self.is_cpu = kwargs['is_cpu'] if 'is_cpu' in kwargs else True
        self.is_black = kwargs['is_black'] if 'is_black' in kwargs else True

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "[CPU:"+self.is_cpu.__str__()+", IS_BLACK:"+self.is_black.__str__()+"]"
