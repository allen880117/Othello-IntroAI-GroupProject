#!/usr/bin/env python3
import board 
import coord
import game_util 
import weight 
import random 
import math 
import time
import copy

COEFF = math.sqrt(2)

class Node():
    """ Class: Node of UCT """

    def __init__(self, _parent: 'Node', _state: board.Board, _step: coord.Coord, _is_black: bool):
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

        start = time.time()
        end   = time.time()
        while start-end < 4.75 :
            V1 = self.tree_policy(self.root)
            delta = self.default_policy(V1.state, V1.is_black)
            self.backup(V1, delta)
            end = time.time()
        
        self.root = self.best_child(self.root, 0)
        self.root.parent = None

        return self.root.step


    def tree_policy(self, _v: Node) -> Node:
        v = copy.deepcopy(_v)
        while not game_util.is_end(v.state):
            if v.is_expandable() :
                return self.expand(v)
            else:
                v = self.best_child(v, COEFF)

        return v
    
    def expand(self, _v:Node) -> Node:
        unchoosed_steps = []
        for step in _v.valid_next_steps:
            is_in_child_list = False
            child: Node
            for child in _v.childs:
                if step == child.step:
                    is_in_child_list = True
                    break
            
            if not is_in_child_list:
                unchoosed_steps.append(step)
        
        idx = random.randint(0, len(unchoosed_steps)-1)
        new_step = unchoosed_steps[idx]
        is_new_color_black = False if _v.is_black else True
        new_state = _v.state
        game_util.do_set_and_flip(new_state, is_new_color_black, new_step)

        new_child = Node(_v, new_state, new_step, is_new_color_black)
        _v.childs.append(new_child)

        return new_child

    def best_child(self, _v:Node, _c:float) -> Node:
        max_ucb = -10e9
        best = None
        child: Node
        for child in _v.childs:
            ucb = child.q / child.n + _c * math.sqrt(math.log(_v.n)/child.n)
            if child.step != coord.NO_ACTION:
                if self.root.is_black:
                    ucb *= self.weight_white.get(child.step.x, child.step.y)
                else:
                    ucb *= self.weight_black.get(child.step.x, child.step.y)

            if ucb > max_ucb:
                max_ucb = ucb
                best = child

        return best

    def default_policy(self, _s:board.Board, _is_black:bool) -> int:
        s = copy.deepcopy(_s)
        is_black = False if _is_black else True
        while not game_util.is_end(s):
            possible_steps = game_util.get_valid_steps(s, is_black)
            step = coord.NO_ACTION
            if len(possible_steps) != 0:
                step = possible_steps[random.randint(0, len(possible_steps)-1)]
                game_util.do_set_and_flip(s, is_black, step)
            is_black = False if is_black else True
        return game_util.get_result(s)
    
    def backup(self, _s:Node, _delta:int) -> None:
        cur = _s
        while cur != None:
            cur.n+=1
            if(cur.is_black and _delta > 0) or (not cur.is_black and _delta<0):
                cur.q+=1

            cur = cur.parent       

