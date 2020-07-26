#include <display.h>
#include <othello.h>
/*
    Before Main Process
*/
void Othello::do_pre_process() {
  this->board.clear();
  this->player_black.set_color(true);
  this->player_white.set_color(false);
  this->do_welcome_event();
}

/*
    The Main Process
*/
void Othello::do_main_process() {
  bool is_black = true;
  while (!GameUtil::is_end(this->board)) {
    /* Print Board */
    Display::clear();
    Display::print(this->board);

    /* There exists Valid Step for this Color */
    std::vector<Coord> valid_steps =
        GameUtil::get_valid_steps(this->board, is_black);
    if (!valid_steps.empty()) {
      /* Ask Player */
      Coord step = NO_ACTION;
      if (is_black) {
        step = player_black.get_step(this->board);
      } else {
        step = player_white.get_step(this->board);
      }

      /* Set the Piece and Flip  */
      GameUtil::do_set_and_flip(this->board, is_black, step);
    }

    /* Reverse Color */
    is_black = (is_black) ? false : true;
  }
}

/*
    After Main Process
*/
void Othello::do_post_process() {
  int result = GameUtil::get_result(this->board);
  if (result == 0) {
    // DRAW
  } else if (result > 0) {
    // Black WIN
  } else {
    // White WIN
  }
}

/*
    Welcome Event
*/
void Othello::do_welcome_event() {
  Display::clear();
  Display::print(this->board);
}

/*
    Start the Game: Public Entry Point
*/
void Othello::start_game() {
  this->do_pre_process();
  this->do_main_process();
  this->do_post_process();
}