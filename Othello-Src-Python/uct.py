#!/usr/bin/env python3
import game_util

from board import (Board, BOARD_H, BOARD_W, Status)
from coord import (Coord, NO_ACTION)
from weight import (Weight)

import copy
import time
import math
import random
from typing import (List)

COEFF = math.sqrt(2)


class Node():
    """ Class: Node """

    def __init__(self, _parent_idx: int, _state: Board, _step: Coord, _is_black: bool):
        self.parent_idx = copy.deepcopy(_parent_idx)
        self.childs_idx = []

        self.state = copy.deepcopy(_state)
        self.step = copy.deepcopy(_step)
        self.is_black = copy.deepcopy(_is_black)
        self.valid_next_steps = []
        self.update_valid_next_steps()

        self.n = 0
        self.q = 0

    def is_expandable(self) -> bool:
        return len(self.valid_next_steps) > len(self.childs_idx)

    def update_valid_next_steps(self) -> List[Coord]:
        # Decide next steps's color, the inverse of current state's color
        is_next_black = not self.is_black
        self.valid_next_steps = game_util.get_valid_steps(
            self.state, is_next_black)

        # There is no possible action, push NO_ACTION
        if len(self.valid_next_steps) == 0:
            self.valid_next_steps.append(NO_ACTION)


class Tree():
    """ Class: UCT Tree """

    def __init__(self):
        self.tree = []
        self.root_idx = -1
        self.weight_black = Weight()
        self.weight_black.reset()
        self.weight_white = Weight()
        self.weight_white.reset()

    def create_node(self, _parent_idx: int, _state: Board, _step: Coord, _is_black: bool) -> int:
        self.tree.append(Node(_parent_idx, _state, _step, _is_black))
        return len(self.tree)-1  # Index of this Node in Tree List

    def uct_search(self, _s0: Board, _is_black: bool) -> Coord:
        if(self.root_idx == -1):
            # Root is not existing
            self.tree = []
            self.root_idx = self.create_node(-1, _s0, NO_ACTION, _is_black)
        else:
            matched = False
            for child_idx in self.tree[self.root_idx].childs_idx:
                if (self.tree[child_idx].state == _s0):
                    # Replace Root
                    self.root_idx = child_idx
                    self.tree[self.root_idx].parent_idx = -1
                    matched = True
                    break

            if not matched:
                self.tree = []
                self.root_idx = self.create_node(-1, _s0, NO_ACTION, _is_black)

        start = time.time()
        end = time.time()
        while end-start < 4.75:
            V1_idx = self.tree_policy(self.root_idx)
            delta = self.default_policy(
                self.tree[V1_idx].state, self.tree[V1_idx].is_black)
            self.backup(V1_idx, delta)
            end = time.time()

        self.root_idx = self.best_child(self.root_idx, 0)
        self.tree[self.root_idx].parent_idx = -1

        return self.tree[self.root_idx].step

    def tree_policy(self, _v_idx: int) -> int:
        # The State is not terminated state
        while not game_util.is_end(self.tree[_v_idx].state):
            if self.tree[_v_idx].is_expandable():
                # Expand the Node
                return self.expand(_v_idx)
            else:
                # Pick Best Child
                _v_idx = self.best_child(_v_idx, COEFF)

        #  Return
        return _v_idx

    def expand(self, _v_idx: int) -> int:
        # Find Unchoosed Steps
        unchoosed_steps = []

        # Do Matching, Find unused next-steps
        for step in self.tree[_v_idx].valid_next_steps:
            # Is this step has been expanded (It has been a a child)
            is_in_child_list = False

            # Search among childs
            for child_idx in self.tree[_v_idx].childs_idx:
                # This Step already been expanded
                if step == self.tree[child_idx].step:
                    is_in_child_list = True
                    break

            # This step hasn't been expanded yet
            if not is_in_child_list:
                unchoosed_steps.append(step)

        # Choose a step from unchoosed next steps
        idx = random.randint(0, len(unchoosed_steps)-1)

        # Do the step
        new_step = unchoosed_steps[idx]
        is_new_color_black = not self.tree[_v_idx].is_black
        new_state = self.tree[_v_idx].state
        game_util.do_set_and_flip(new_state, is_new_color_black, new_step)

        # Create and Push new child into child list
        new_child_idx = self.create_node(
            _v_idx, new_state, new_step, is_new_color_black)
        self.tree[_v_idx].childs_idx.append(new_child_idx)

        # Return this new child_idx
        return new_child_idx

    def best_child(self, _v_idx: int, _c: float) -> int:
        """
            Retrun Best Child
            We use UCB and Weight here to choose best one
            Calculate the Score of each Child, and Pick Best one
        """
        # Max value for picking best child
        max_ucb = -10e9
        best = None

        # Calculate the score of each child, and pick best one
        for child_idx in self.tree[_v_idx].childs_idx:
            # Calculate UCB
            ucb = self.tree[child_idx].q/self.tree[child_idx].n
            ucb += _c * \
                math.sqrt(math.log(self.tree[_v_idx].n)/self.tree[child_idx].n)

            # Weight
            if self.tree[child_idx].step != NO_ACTION:
                if (self.tree[self.root_idx].is_black):
                    # Opponent's color is black
                    # We are the white one
                    ucb *= self.weight_white.get(self.tree[child_idx].step)
                else:
                    ucb *= self.weight_black.get(self.tree[child_idx].step)

            # Compare
            if ucb > max_ucb:
                max_ucb = ucb
                best = child_idx

        # Return Best One
        return best

    def default_policy(self, _s: Board, _is_black: bool) -> int:
        """
            The default policy of the game (Simulation)
            (_is_black is the Last Pieces's Color)
        """
        # Reverse color for next player
        is_black = not _is_black

        # Copy Board
        s = copy.deepcopy(_s)

        # Random Play
        while not game_util.is_end(s):
            # Get all possible steps
            possible_steps = game_util.get_valid_steps(s, is_black)

            #  Set Piece
            if len(possible_steps) != 0:
                step = possible_steps[random.randint(0, len(possible_steps)-1)]
                game_util.do_set_and_flip(s, is_black, step)

            # Reverse Color
            is_black = not is_black

        # Return Final Result
        return game_util.get_result(s)

    def backup(self, _v_idx: int, _delta: int) -> None:
        """ Back Propagation """
        while _v_idx != -1 and _v_idx != None:
            # Touch Counter add 1
            self.tree[_v_idx].n += 1

            # Win Counter add 1
            if (self.tree[_v_idx].is_black and _delta > 0) or ((not self.tree[_v_idx].is_black) and _delta < 0):
                self.tree[_v_idx].q += 1

            _v_idx = self.tree[_v_idx].parent_idx
