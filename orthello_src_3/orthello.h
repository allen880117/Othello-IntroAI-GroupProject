#pragma once
#include "integrate.h"

class Orthello {
 public:
  Board_t board;

 public:
  Orthello() {
    this->clear();
    srand(time(NULL));
  }
  void        start_game();
  vector<int> GetStep(Board_t &__board, bool is_black);
  vector<int> GetStep2(Board_t &__board, bool is_black);
  void        clear();
  void        print();
};

void Orthello::start_game() {
  /* Initialize Board */
  uct.clear();
  this->clear();
  bool is_black = true;

  WeightLog weight_log(false);
  /* Play */
  while (!GameControl::is_end(this->board)) {
    // printf(W_CLEAR);
    // this->print();

    vector<int> step = GetStep(this->board, is_black);
    if (step[0] != -1 && step[1] != -1) {
      GameControl::set_and_flip(this->board, Coord_t(step[0], step[1]),
                                is_black);
      if (!is_black) weight_log.record(Coord_t(step[0], step[1]));
    }

    // printf(W_CLEAR);
    // this->print();

    is_black = (is_black) ? false : true;  // Change Color
  }

  weight_log.end(GameControl::get_result((this->board)));
  printf("%s\n", GameControl::get_result(this->board) == BLACK_WIN
                     ? "BLACK WIN"
                     : "WHITE WIN");

  /* Initialize Board */
  uct.clear();
  this->clear();
  is_black = true;

  WeightLog weight_log2(true);
  /* Play */
  while (!GameControl::is_end(this->board)) {
    // printf(W_CLEAR);
    // this->print();

    vector<int> step = GetStep2(this->board, is_black);
    if (step[0] != -1 && step[1] != -1) {
      GameControl::set_and_flip(this->board, Coord_t(step[0], step[1]),
                                is_black);
      if (is_black) weight_log2.record(Coord_t(step[0], step[1]));
    }

    // printf(W_CLEAR);
    // this->print();

    is_black = (is_black) ? false : true;  // Change Color
  }

  weight_log2.end(GameControl::get_result((this->board)));
  printf("%s\n", GameControl::get_result(this->board) == BLACK_WIN
                     ? "BLACK WIN"
                     : "WHITE WIN");
}

vector<int> Orthello::GetStep(Board_t &__board, bool is_black) {
  /* Declare Return Step */
  vector<int> ret_step;
  ret_step.resize(2);

  ret_step[0] = -1;
  ret_step[1] = -1;

  vector<Coord_t> valid_pos = GameControl::get_valid_pos(__board, is_black);
  if (valid_pos.empty()) return ret_step;

  if (is_black) {
    Coord_t step = valid_pos[rand() % valid_pos.size()];
    ret_step[0]  = step.first;
    ret_step[1]  = step.second;
    return ret_step;

  } else {
    Action_t act = uct.uct_search(__board, BLACK);  // Color is the last piece
    ret_step[0]  = act.first;
    ret_step[1]  = act.second;
    return ret_step;
  }
}

vector<int> Orthello::GetStep2(Board_t &__board, bool is_black) {
  /* Declare Return Step */
  vector<int> ret_step;
  ret_step.resize(2);

  ret_step[0] = -1;
  ret_step[1] = -1;

  vector<Coord_t> valid_pos = GameControl::get_valid_pos(__board, is_black);
  if (valid_pos.empty()) return ret_step;

  if (!is_black) {
    Coord_t step = valid_pos[rand() % valid_pos.size()];
    ret_step[0]  = step.first;
    ret_step[1]  = step.second;
    return ret_step;

  } else {
    Action_t act = uct.uct_search(__board, WHITE);  // Color is the last piece
    ret_step[0]  = act.first;
    ret_step[1]  = act.second;
    return ret_step;
  }
}

void Orthello::print() {
  printf("  0 1 2 3 4 5 6 7\n");
  for (int i = 0; i < HEIGHT; i++) {
    printf(W_NORMAL " ");
    for (int k = 0; k < WIDTH * 2 + 1; k++) printf(B_GREEN_F_BLACK "=");
    printf("\n");

    printf(W_NORMAL "%d", i);
    for (int j = 0; j < WIDTH; j++) {
      if (this->board[i][j] == ILLEGAL) {
        printf(B_GREEN_F_BLACK "|X");
      } else if (this->board[i][j] == BLACK) {
        printf(B_GREEN_F_BLACK "|" B_BLACK " ");
      } else if (this->board[i][j] == WHITE) {
        printf(B_GREEN_F_BLACK "|" B_WHITE " ");
      } else {
        printf(B_GREEN_F_BLACK "| ");
      }
    }

    printf(B_GREEN_F_BLACK "|\n");
  }

  printf(W_NORMAL " ");
  for (int k = 0; k < WIDTH * 2 + 1; k++) printf(B_GREEN_F_BLACK "=");
  printf("\n" W_NORMAL);
}

void Orthello::clear() {
  /* Initialize */
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      this->board[i][j] = UNOCCUPIED;
    }
  }

  /* Set Four Corner */
  this->board[0][0]                  = ILLEGAL;
  this->board[0][WIDTH - 1]          = ILLEGAL;
  this->board[HEIGHT - 1][0]         = ILLEGAL;
  this->board[HEIGHT - 1][WIDTH - 1] = ILLEGAL;
}
