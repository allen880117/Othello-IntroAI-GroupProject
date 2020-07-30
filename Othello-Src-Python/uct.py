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

    def __init__(self, _parent: Node, _state: board.Board, _step: coord.Coord, _is_black: bool):
        """ Constructor """
        self.parent = _parent
        self.childs = []

        self.state = _state
        self.step = _step
        self.is_black = _is_black

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
        """ 
            Do Search in UCT 
            (_is_black is the Last Pieces's Color)    
        """
        if (self.root == None):
            self.root = Node(None, _s0, coord.NO_ACTION, _is_black)
        else:
            matched = False
            child: Node
            for child in self.root.childs:
                if child.state == _s0:
                    self.root = child
                    self.root.parent = None
                    matched = True
                    break

            if not matched:
                self.root = Node(None, _s0, coord.NO_ACTION, _is_black)
