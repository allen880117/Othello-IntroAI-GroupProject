#!/usr/bin/env python3

import board as board

# Color Definition
B_GREEN_F_BLACK = "\033[0;30;42m"
B_BLACK = "\033[0;40m"
B_WHITE = "\033[0;47m"
NORMAL = "\033[0m"
CLEAR = "\033[2J\033[1;1H"


def clear():
    """ Clear the Screen """
    print(CLEAR, end='')


def display(_board: board.Board):
    """ Print the Board """
    if(type(_board) == board.Board):
        print('  ', end='')
        for i in range(board.BOARD_W):
            print("%d " % (i), end='')
        print('')

        for r in range(board.BOARD_H):
            print(NORMAL+" ", end='')
            for _ in range(board.BOARD_W*2+1):
                print(B_GREEN_F_BLACK+"=", end='')
            print(NORMAL)

            print(NORMAL+"%d" % (r), end='')

            for c in range(board.BOARD_W):
                status = _board.get(r, c)
                if(status == board.Status.ILLEGAL):
                    print(B_GREEN_F_BLACK+"|X", end='')
                elif(status == board.Status.BLACK):
                    print(B_GREEN_F_BLACK+"|"+B_BLACK+" ", end='')
                elif(status == board.Status.WHITE):
                    print(B_GREEN_F_BLACK+"|"+B_WHITE+" ", end='')
                else:
                    print(B_GREEN_F_BLACK+"| ", end='')

            print(B_GREEN_F_BLACK+"|")

        print(NORMAL+" ", end='')
        for _ in range(board.BOARD_W*2+1):
            print(B_GREEN_F_BLACK+"=", end='')
        print(NORMAL)