#!/usr/bin/env python3
import board as board
import coord as coord
import uct as uct
import game_util as game_util


class Player():
    def __init__(self, **kwargs):
        """ Constructor """
        for key in kwargs.keys():
            if key != 'is_cpu' and key != 'is_black':
                raise BaseException(
                    'Error Key Argument for Player Constructor')

        self.is_cpu = kwargs['is_cpu'] if 'is_cpu' in kwargs else True
        self.is_black = kwargs['is_black'] if 'is_black' in kwargs else True

        self.uct = uct.Tree()

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "[CPU:"+self.is_cpu.__str__()+", IS_BLACK:"+self.is_black.__str__()+"]"

    def set_color(self, _is_black: bool) -> None:
        self.is_black = _is_black

    def set_cpu(self, _is_cpu: bool) -> None:
        self.is_cpu = _is_cpu

    def get_step(self, _board: board.Board) -> coord.Coord:
        step = coord.NO_ACTION
        if(self.is_cpu):
            # Do UCT Search
            # Color is the Last Pieces's Color
            step = self.uct.uct_search(_board, not (self.is_black))
        else:
            while(True):
                r, c = input(
                    'Please input valid step in format < r  c >: ').split()
                step = coord.Coord(r, c)
                if(game_util.is_valid_step(_board, self.is_black, step)):
                    break

        return step
