#!/usr/bin/env python3
import board as board
import coord as coord
import game_util as game_util
import weight as weight
import random as random
import math as math

COEFF = math.sqrt(2)


class Node():
    """ Class: Node of UCT """

    def __init__(self, **kwargs):
        """ Constructor """
        self.parent = kwargs['parent']
        self.childs = []

        self.state = kwargs['state']
        self.step = kwargs['step']
        self.is_black = kwargs['is_black']

        self.valid_next_steps = []
        self.update_valid_next_steps()

        self.n = 0
        self.q = 0

    def is_expandable(self) -> bool:
        return len(self.valid_next_steps) > len(self.childs)

    def update_valid_next_steps(self) -> list:
        """ 
          Update the possible next steps
          If there is no possible next step for this state, 
          We will add NO_ACTION as only possible step
        """
        """ Decide next step's color, the inverse of current state's color """
        is_next_black = False if self.is_black else True
        self.valid_next_steps = game_util.get_valid_steps(
            self.state, is_next_black)

        """ There is no possible action, push NO_ACTION """
        if len(self.valid_next_steps) == 0:
            self.valid_next_steps.append(coord.NO_ACTION)


class Tree():
    def __init__(self):
        self.root = None
        self.weight_black = weight.Weight()
        self.weight_white = weight.Weight()

    def uct_search(self, _s0: board.Board, _is_black: bool) -> coord.Coord:
        return coord.NO_ACTION
