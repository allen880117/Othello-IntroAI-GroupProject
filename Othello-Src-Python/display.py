#!/usr/bin/env python3

import board as board

# Color Definition 
B_GREEN_F_BLACK="\033[0;30;42m"
B_BLACK="\033[0;40m"
B_WHITE="\033[0;47m"
NORMAL="\033[0m"
CLEAR="\033[2J\033[1;1H"

def clear():
    """ Clear the Screen """
    print(CLEAR, end='')

def display(_board):
    """ Print the Board """
    if(type(_board) == board.Board):
        pass