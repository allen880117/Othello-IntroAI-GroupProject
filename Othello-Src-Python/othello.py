#!/usr/bin/env python3
import display
import othello
import board
import player
import game_util
import coord


class Othello():
    """ Class: Othello """

    def __init__(self):
        self.board = board.Board()
        self.player_black = player.Player()
        self.player_white = player.Player()

    def do_pre_process(self) -> None:
        self.board.clear()
        self.player_black.set_color(True)
        self.player_white.set_color(False)
        self.do_welcome_event

    def do_main_process(self) -> None:
        is_black = True

        # Print Board
        display.clear()
        display.display(self.board)

        while not game_util.is_end(self.board):

            # There exists valid step for this color
            valid_steps = game_util.get_valid_steps(self.board, is_black)

            if len(valid_steps) != 0:
                # Ask Player
                step = coord.NO_ACTION
                if is_black:
                    step = self.player_black.get_step(self.board)
                else:
                    step = self.player_white.get_step(self.board)

                game_util.do_set_and_flip(self.board, is_black, step)

            # Reverse Color
            is_black = not is_black

            # Print Board
            display.clear()
            display.display(self.board)

    def do_post_process(self) -> None:
        result = game_util.get_result(self.board)
        if result == 0:
            # Draw
            print("Draw")
        elif result > 0:
            # Black Win
            print("Black Win, %d" % (result))
        else:
            # White Win
            print("White Win, %d" % (-result))

    def do_welcome_event(self) -> None:
        display.clear()
        display.display(self.board)

    def start_game(self) -> None:
        self.do_pre_process()
        self.do_main_process()
        self.do_post_process()
