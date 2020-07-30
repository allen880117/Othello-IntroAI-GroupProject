#!/usr/bin/env python3
import board as board


class Weight():
    """ Class: Weight """

    def __init__(self):
        self.weight = []
        for r in range(board.BOARD_H):
            self.weight.append([])
            for _ in range(board.BOARD_W):
                self.weight[r].append(1.0)

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        msg = ''
        for r in range(board.BOARD_H):
            for c in range(board.BOARD_W):
                msg += str(self.weight[r][c]) + ' '
            msg += '\n'
        return msg

    def reset(self):
        for r in range(board.BOARD_H):
            for c in range(board.BOARD_W):
                self.weight[r][c] = 1.0

    def set(self, _r: int, _c: int, _value: float) -> None:
        self.weight[_r][_c] = _value

    def get(self, _r: int, _c: int) -> float:
        return self.weight[_r][_c]
