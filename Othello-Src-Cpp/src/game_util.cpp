#include <game_util.h>

/*
  Check Whether the board is in termintaed state or not
*/
bool GameUtil::is_end(Board &__board) {
  /* Traverse Board */
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      /* Only Need to Check the cells that are unoccupied */
      if (__board.get(r, c) == Status::UNOCCUPIED) {
        /* There exists at least a valid step for one of the color */
        if (GameUtil::is_valid_step(__board, true, Coord(r, c)) ||
            GameUtil::is_valid_step(__board, false, Coord(r, c))) {
          /* The Game is not over yet */
          return false;
        }
      }
    }
  }

  /* We can't find valid step */
  return true;
}

/*
  Check Whether this step is valid in current state of board
*/
bool GameUtil::is_valid_step(Board &__board, bool __is_black, Coord __step) {
  /* Abort */
  if (__step == NO_ACTION) return false;

  /* You can't set piece on not UNOCCUPIED */
  if (__board.get(__step.first, __step.second) != Status::UNOCCUPIED)
    return false;

  /* Inside Safe Area (Central 6x6), No need to check */
  if ((__step.first >= 1 && __step.first <= BOARD_H - 2) &&
      (__step.second >= 1 && __step.second <= BOARD_W - 2))
    return true;

  /*
    [B]    [W]     [...][B]
    [start][middle][...][end]
  */
  Status middle_color = (__is_black) ? Status::WHITE : Status::BLACK;
  Status end_color    = (__is_black) ? Status::BLACK : Status::WHITE;

  /* Eight Directions */
  for (Coord dir : direction) {
    /* Reset */
    int cur_r = __step.first;
    int cur_c = __step.second;
    int state = 0;

    /* Step Out */
    cur_r += dir.first;
    cur_c += dir.second;

    /* Check */
    while (__board.check_boundary(cur_r, cur_c)) {
      if (state == 0 && __board.get(cur_r, cur_c) == middle_color) {
        /* [B][W] */
        state = 1;
      } else if (state == 1 && __board.get(cur_r, cur_c) == middle_color) {
        /* [B][W][...] */
        state = 1;
      } else if (state == 1 && __board.get(cur_r, cur_c) == end_color) {
        /* [B][W][...][B] */
        return true;
      } else {
        /* Other Fail Situation */
        break;
      }

      /* Step Out */
      cur_r += dir.first;
      cur_c += dir.second;
    }
  }

  /* Fail */
  return false;
}

/*
  Set the Piece on Board, and Flip
*/
bool GameUtil::do_set_and_flip(Board &__board, bool __is_black, Coord __step) {
  /* Abort */
  if (__step == NO_ACTION) return false;

  /* You can't set piece on not UNOCCUPIED */
  if (__board.get(__step.first, __step.second) != Status::UNOCCUPIED)
    return false;

  /* Set the piece */
  __board.set(__step.first, __step.second,
              (__is_black) ? Status::BLACK : Status::WHITE);

  /*
    [B]    [W]     [...][B]
    [start][middle][...][end]
  */
  Status middle_color = (__is_black) ? Status::WHITE : Status::BLACK;
  Status end_color    = (__is_black) ? Status::BLACK : Status::WHITE;

  /* Eight Directions */
  bool ret_status = false;
  for (Coord dir : direction) {
    /* Reset */
    int cur_r = __step.first;
    int cur_c = __step.second;
    int state = 0;

    /* Step Out */
    cur_r += dir.first;
    cur_c += dir.second;

    /* Check */
    while (__board.check_boundary(cur_r, cur_c)) {
      if (state == 0 && __board.get(cur_r, cur_c) == middle_color) {
        /* [B][W] */
        state = 1;

      } else if (state == 1 && __board.get(cur_r, cur_c) == middle_color) {
        /* [B][W][...] */
        state = 1;

      } else if (state == 1 && __board.get(cur_r, cur_c) == end_color) {
        /* [B][W][...][B] */
        ret_status = true;

        /* Do Flip */
        while (Coord(cur_r, cur_c) != __step) {
          __board.set(cur_r, cur_c, end_color);
          cur_r -= dir.first;
          cur_c -= dir.second;
        }

        /* Change Direction */
        break;

      } else {
        /* Other Fail Situation */
        break;
      }

      /* Step Out */
      cur_r += dir.first;
      cur_c += dir.second;
    }
  }

  if (ret_status) {
    return true;
  } else {
    /* Inside Safe Area (Central 6x6), "No Flip" is legal */
    if ((__step.first >= 1 && __step.first <= BOARD_H - 2) &&
        (__step.second >= 1 && __step.second <= BOARD_W - 2)) {
      return true;
    } else {
      /* Illegal Movement, Recover the board */
      __board.set(__step.first, __step.second, Status::UNOCCUPIED);
      return false;
    }
  }
}

/*
  Return the difference ([#B] - [#W])
*/
int GameUtil::get_result(Board &__board) {
  int black_counter = 0;
  int white_counter = 0;
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      if (__board.get(r, c) == Status::BLACK)
        black_counter++;
      else if (__board.get(r, c) == Status::WHITE)
        white_counter++;
    }
  }

  return black_counter - white_counter;
}