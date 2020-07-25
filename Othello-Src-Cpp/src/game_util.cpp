#include <game_util.h>

/*
  Check Whether the board is in termintaed state or not
*/
bool GameUtil::is_end(Board &_board) {
  /* Traverse Board */
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      /* Only Need to Check the cells that are unoccupied */
      if (_board.get(r, c) == Status::UNOCCUPIED) {
        /* There exists at least a valid step for one of the color */
        if (GameUtil::is_valid_step(_board, true, Coord(r, c)) ||
            GameUtil::is_valid_step(_board, false, Coord(r, c))) {
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
bool GameUtil::is_valid_step(Board &_board, bool _is_black, Coord _step) {
  /* Abort */
  if (_step == NO_ACTION) return false;

  /* You can't set piece on not UNOCCUPIED */
  if (_board.get(_step.first, _step.second) != Status::UNOCCUPIED) return false;

  /* Inside Safe Area (Central 6x6), No need to check */
  if ((_step.first >= 1 && _step.first <= BOARD_H - 2) &&
      (_step.second >= 1 && _step.second <= BOARD_W - 2))
    return true;

  /*
    [B]    [W]     [...][B]
    [start][middle][...][end]
  */
  Status middle_color = (_is_black) ? Status::WHITE : Status::BLACK;
  Status end_color    = (_is_black) ? Status::BLACK : Status::WHITE;

  /* Eight Directions */
  for (Coord dir : direction) {
    /* Reset */
    int cur_r = _step.first;
    int cur_c = _step.second;
    int state = 0;

    /* Check */
    while (_board.check_boundary(cur_r, cur_c)) {
      /* Step Out */
      cur_r += dir.first;
      cur_c += dir.second;

      if (state == 0 && _board.get(cur_r, cur_c) == middle_color) {
        /* [B][W] */
        state = 1;
      } else if (state == 1 && _board.get(cur_r, cur_c) == middle_color) {
        /* [B][W][...] */
        state = 1;
      } else if (state == 1 && _board.get(cur_r, cur_c) == end_color) {
        /* [B][W][...][B] */
        return true;
      } else {
        /* Other Fail Situation */
        break;
      }
    }
  }

  /* Fail */
  return false;
}

/*
  Set the Piece on Board, and Flip
*/
bool GameUtil::do_set_and_flip(Board &_board, bool _is_black, Coord _step) {
  /* Abort */
  if (_step == NO_ACTION) return false;

  /* You can't set piece on not UNOCCUPIED */
  if (_board.get(_step.first, _step.second) != Status::UNOCCUPIED) return false;

  /* Set the piece */
  _board.set(_step.first, _step.second,
             (_is_black) ? Status::BLACK : Status::WHITE);

  /*
    [B]    [W]     [...][B]
    [start][middle][...][end]
  */
  Status middle_color = (_is_black) ? Status::WHITE : Status::BLACK;
  Status end_color    = (_is_black) ? Status::BLACK : Status::WHITE;

  /* Eight Directions */
  bool ret_status = false;
  for (Coord dir : direction) {
    /* Reset */
    int cur_r = _step.first;
    int cur_c = _step.second;
    int state = 0;

    /* Check */
    while (_board.check_boundary(cur_r, cur_c)) {
      /* Step Out */
      cur_r += dir.first;
      cur_c += dir.second;

      if (state == 0 && _board.get(cur_r, cur_c) == middle_color) {
        /* [B][W] */
        state = 1;

      } else if (state == 1 && _board.get(cur_r, cur_c) == middle_color) {
        /* [B][W][...] */
        state = 1;

      } else if (state == 1 && _board.get(cur_r, cur_c) == end_color) {
        /* [B][W][...][B] */
        ret_status = true;

        /* Do Flip */
        while (Coord(cur_r, cur_c) != _step) {
          _board.set(cur_r, cur_c, end_color);
          cur_r -= dir.first;
          cur_c -= dir.second;
        }

        /* Change Direction */
        break;

      } else {
        /* Other Fail Situation */
        break;
      }
    }
  }

  if (ret_status) {
    return true;
  } else {
    /* Inside Safe Area (Central 6x6), "No Flip" is legal */
    if ((_step.first >= 1 && _step.first <= BOARD_H - 2) &&
        (_step.second >= 1 && _step.second <= BOARD_W - 2)) {
      return true;
    } else {
      /* Illegal Movement, Recover the board */
      _board.set(_step.first, _step.second, Status::UNOCCUPIED);
      return false;
    }
  }
}

/*
  Return all the possible step for this color (at this state)
*/
std::vector<Coord> GameUtil::get_valid_steps(Board &_board, bool _is_black) {
  std::vector<Coord> ret;
  ret.clear();
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      if (GameUtil::is_valid_step(_board, _is_black, Coord(r, c)))
        ret.push_back(Coord(r, c));
    }
  }
  return ret;
}

/*
  Return the difference ([#B] - [#W])
*/
int GameUtil::get_result(Board &_board) {
  int black_counter = 0;
  int white_counter = 0;
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      if (_board.get(r, c) == Status::BLACK)
        black_counter++;
      else if (_board.get(r, c) == Status::WHITE)
        white_counter++;
    }
  }

  return black_counter - white_counter;
}
