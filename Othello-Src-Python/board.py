#!/usr/bin/env python3
from enum import Enum
from copy import deepcopy

# Board Size
BOARD_H = 8
BOARD_W = 8
board_size = (BOARD_H, BOARD_W)


class Status(Enum):
    # Board Status of Cell
    UNOCCUPIED = 0
    BLACK = 1
    WHITE = 2
    ILLEGAL = 3


class Board():
    """ Class Board """

    def __init__(self):
        self.board = []
        self.clear()

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        msg = ""
        for r in range(BOARD_H):
            for c in range(BOARD_W):
                msg += str(self.board[r][c].value) + ' '
            msg += '\n'
        return msg

    def __eq__(self, rhs):
        return self.board == rhs.board

    def clear(self):
        for r in range(BOARD_H):
            self.board.append([])
            for _ in range(BOARD_W):
                self.board[r].append(Status.UNOCCUPIED)

        self.board[0][0] = Status.ILLEGAL
        self.board[0][BOARD_W-1] = Status.ILLEGAL
        self.board[BOARD_H-1][0] = Status.ILLEGAL
        self.board[BOARD_H-1][BOARD_W-1] = Status.ILLEGAL

    def get(self, _x, _y):
        if(self.check_boundary(_x, _y)):
            return self.board[_x][_y] 
        else:
            return Status.ILLEGAL
            
    def set(self, _x, _y, _value):
        if(self.check_boundary(_x, _y)):
            if(type(_value) == int):
                self.board[_x][_y] = Status(_value)
            elif(type(_value) == type(Status.UNOCCUPIED)):
                self.board[_x][_y] = _value

    def check_boundary(self, _x, _y):
        return (0 <= _x) and (_x < BOARD_H) and (0 <= _y) and (_y < BOARD_W)
