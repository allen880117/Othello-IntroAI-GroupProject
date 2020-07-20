#include <othello.h>

void Othello::do_pre_process() {
  this->board.clear();
  this->p1.set_color(true);
  this->p2.set_color(false);
  this->exist_valid_white = true;
  this->exist_valid_white = true;
  this->do_welcome_event();
}

void Othello::do_main_process() {
  bool is_black = true;
  while (!this->is_end()) {
    /* Print Board */
    W_CLEAR;
    this->board.print();

    /* Ask Player */
    Coord step = NO_ACTION;
    if (is_black && this->exist_valid_black) {
      step = p1.get_step(this->board);
    } else if (!is_black && this->exist_valid_white) {
      step = p2.get_step(this->board);
    }

    /* Set the Piece and Flip  */
    this->do_set_and_flip(step);

    /* Reverse Color */
    is_black = (is_black) ? false : true;
  }
}

void Othello::do_post_process() {}

void Othello::do_welcome_event() {
  W_CLEAR;
  this->board.print();
}

bool Othello::is_end() {
  this->exist_valid_white = this->is_exist_valid_step(false);
  this->exist_valid_black = this->is_exist_valid_step(true);
  return (!this->exist_valid_white) && (!this->exist_valid_black);
}

bool Othello::is_exist_valid_step(bool __is_black) {}

void Othello::do_set_and_flip(Coord __step) {
  if (__step == NO_ACTION) return;
}

void Othello::start_game() {
  this->do_pre_process();
  this->do_main_process();
  this->do_post_process();
}