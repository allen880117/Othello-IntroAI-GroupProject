#pragma once
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <array>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/* Color Definition */
#define B_GREEN_F_BLACK "\033[0;30;42m"
#define B_BLACK "\033[0;40m"
#define B_WHITE "\033[0;47m"
#define W_NORMAL "\033[0m"
#define W_CLEAR "\033[2J\033[1;1H"

/* The Status of Each Cell of Board */
#define UNOCCUPIED 0
#define BLACK 1
#define WHITE 2
#define ILLEGAL -1

/* The Final Result */
#define DRAW 0
#define BLACK_WIN 1
#define WHITE_WIN 2

/* Board Size */
#define HEIGHT 8
#define WIDTH 8

/* UCT Class Declaration*/
class UCT_Node;
class UCT_Tree;

/* Type Define */
typedef array<array<int, 8>, 8> Board_t;
typedef pair<int, int>          Coord_t;
typedef int                     Color_t;

/* UCT Type Define */
typedef Board_t   State_t;
typedef Coord_t   Action_t;
typedef UCT_Node *Vertex_t;
typedef int       Result_t;

/* Special Action */
#define NO_ACTION Coord_t(-1, -1)

/* Direction <r, c> */
Coord_t direction[] = {Coord_t(-1, -1), Coord_t(-1, 0), Coord_t(-1, 1),
                       Coord_t(0, -1),  Coord_t(0, 1),  Coord_t(1, -1),
                       Coord_t(1, 0),   Coord_t(1, 1)};

/* Weight */
double weight[] = {
    0.0,   100.0, -10.0, 10.0, 10.0, -10,   100.0, 0.0,    // r0
    100.0, -50.0, -25.0, 1.0,  1.0,  -25.0, -50.0, 100.0,  // r1
    -10.0, -25.0, 3.0,   2.0,  2.0,  3.0,   -25.0, -10.0,  // r2
    10.0,  1.0,   2.0,   -1.0, -1.0, 2.0,   1.0,   10.0,   // r3
    10.0,  1.0,   2.0,   -1.0, -1.0, 2.0,   1.0,   10.0,   // r4
    -10.0, -25.0, 3.0,   2.0,  2.0,  3.0,   -25.0, -10.0,  // r5
    100.0, -50.0, -25.0, 1.0,  1.0,  -25.0, -50.0, 100.0,  // r6
    0.0,   100.0, -10.0, 10.0, 10.0, -10,   100.0, 0.0,    // r7
};

double weight2[] = {
    1.0,    1000.0, 1.0, 1.0, 1.0, 1.0, 1000.0, 1.0,     // r0
    1000.0, 1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1000.0,  // r1
    1.0,    1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1.0,     // r2
    1.0,    1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1.0,     // r3
    1.0,    1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1.0,     // r4
    1.0,    1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1.0,     // r5
    1000.0, 1.0,    1.0, 1.0, 1.0, 1.0, 1.0,    1000.0,  // r6
    1.0,    1000.0, 1.0, 1.0, 1.0, 1.0, 1000.0, 1.0,     // r7
};

double weight3[] = {
    /*c0    c1    c2     c3    c4   c5    c6    c7    */
    0.0,  2.5,  1.0,  1.15, 1.15, 1.0,  2.5,  0.0,   // r0
    2.5,  0.85, 0.9,  1.1,  1.1,  0.9,  0.85, 2.5,   // r1
    1.0,  0.9,  1.12, 1.07, 1.07, 1.12, 0.9,  1.0,   // r2
    1.15, 1.1,  1.07, 1.03, 1.03, 1.07, 1.1,  1.15,  // r3
    1.15, 1.1,  1.07, 1.03, 1.03, 1.07, 1.1,  1.15,  // r4
    1.0,  0.9,  1.12, 1.07, 1.07, 1.12, 0.9,  1.0,   // r5
    2.5,  0.85, 0.9,  1.1,  1.1,  0.9,  0.85, 2.5,   // r6
    0.0,  2.5,  1.0,  1.15, 1.15, 1.0,  2.5,  0.0,   // r7
};

double weight4[64];
double weight4_2[64];

class WeightLog {
 public:
  int             id;
  vector<Coord_t> steps;
  bool            is_black;

 public:
  WeightLog(int __id, bool __is_black) {
    this->id = __id;
    this->is_black = __is_black;
    this->steps.clear();

    FILE *weight_file;
    if (this->is_black) {
      if (id == 1) weight_file = fopen("weight_black", "r");
      if (id == 2) weight_file = fopen("weight_black_2", "r");
    } else {
      if (id == 1) weight_file = fopen("weight_white", "r");
      if (id == 2) weight_file = fopen("weight_white_2", "r");
    }

    for (int i = 0; i < 64; i++) {
      if (id == 1) fscanf(weight_file, "%lf", &(weight4[i]));
      if (id == 2) fscanf(weight_file, "%lf", &(weight4_2[i]));
    }
    fclose(weight_file);
  }

  void record(Coord_t __step) { this->steps.push_back(__step); }

  void end(Result_t __result) {
    // double delta = ((double)1.0) / ((double)this->steps.size()) * ;
    double delta = ((double)0.5) / ((double)600);
    if (this->is_black && __result == BLACK_WIN) {
      for (Coord_t step : this->steps) {
        if (id == 1) weight4[step.first * 8 + step.second] += delta;
        if (id == 2) weight4_2[step.first * 8 + step.second] += delta;
      }
    } else if (this->is_black && __result == WHITE_WIN) {
      for (Coord_t step : this->steps) {
        if (id == 1) weight4[step.first * 8 + step.second] -= delta;
        if (id == 2) weight4_2[step.first * 8 + step.second] -= delta;
      }
    } else if (!this->is_black && __result == WHITE_WIN) {
      for (Coord_t step : this->steps) {
        if (id == 1) weight4[step.first * 8 + step.second] += delta;
        if (id == 2) weight4_2[step.first * 8 + step.second] += delta;
      }
    } else if (!this->is_black && __result == BLACK_WIN) {
      for (Coord_t step : this->steps) {
        if (id == 1) weight4[step.first * 8 + step.second] -= delta;
        if (id == 2) weight4_2[step.first * 8 + step.second] -= delta;
      }
    }

    FILE *weight_file;
    if (this->is_black) {
      if (id == 1) weight_file = fopen("weight_black", "w");
      if (id == 2) weight_file = fopen("weight_black_2", "w");
    } else {
      if (id == 1) weight_file = fopen("weight_white", "w");
      if (id == 2) weight_file = fopen("weight_white_2", "w");
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (this->id == 1) fprintf(weight_file, "%lf", (weight4[i * 8 + j]));
        if (this->id == 2) fprintf(weight_file, "%lf", (weight4_2[i * 8 + j]));
        fprintf(weight_file, " ");
      }
      fprintf(weight_file, "\n");
    }
    fclose(weight_file);
  }
};

/* Function of Game Control  */
namespace GameControl {
void            set_and_flip(Board_t &__board, Coord_t __pos, bool is_black);
vector<Coord_t> get_valid_pos(Board_t &__board, bool is_black);
Result_t        get_result(Board_t &__board);

bool is_valid_movement(Board_t &__board, Coord_t __pos, bool is_black);
bool is_in_bound(Coord_t __pos);
bool is_end(Board_t &__board);
};  // namespace GameControl

/* Set and Flip (Please Ensure Validility First) */
void GameControl::set_and_flip(Board_t &__board, Coord_t __pos, bool is_black) {
  /* Abort When No Action */
  if (__pos == NO_ACTION) return;

  /* Color */
  int middle_color = (is_black) ? WHITE : BLACK;
  int end_color    = (is_black) ? BLACK : WHITE;

  /* Set */
  __board[__pos.first][__pos.second] = (is_black) ? BLACK : WHITE;

  /* Eight Direction */
  for (int i = 0; i < 8; i++) {
    /* Reset Current Position */
    int cur_r = __pos.first;
    int cur_c = __pos.second;
    int state = 0;

    /* Step out */
    cur_r += direction[i].first;
    cur_c += direction[i].second;

    /* Check */
    while (is_in_bound(Coord_t(cur_r, cur_c))) {
      if (state == 0 && __board[cur_r][cur_c] == middle_color) {
        /* [B][W] */
        state = 1;
      } else if (state == 1 && __board[cur_r][cur_c] == middle_color) {
        /* [B][W][...] */
        state = 1;
      } else if (state == 1 && __board[cur_r][cur_c] == end_color) {
        /* [B][W][...][B], Do Flip */
        while (Coord_t(cur_r, cur_c) != __pos) {
          __board[cur_r][cur_c] = end_color;
          cur_r -= direction[i].first;
          cur_c -= direction[i].second;
        }
        break;
      } else {
        /* Other Fail Situation */
        break;
      }

      /* Step Out */
      cur_r += direction[i].first;
      cur_c += direction[i].second;
    }
  }
}

/* Get Valid Positions/Actions */
vector<Coord_t> GameControl::get_valid_pos(Board_t &__board, bool is_black) {
  vector<Coord_t> ret;
  ret.clear();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (is_valid_movement(__board, Coord_t(i, j), is_black))
        ret.push_back(Coord_t(i, j));
    }
  }
  return ret;
}

/* Calculate Final Result */
int GameControl::get_result(Board_t &__board) {
  int black_counter = 0;
  int white_counter = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (__board[i][j] == BLACK)
        black_counter++;
      else if (__board[i][j] == WHITE)
        white_counter++;
    }
  }

  if (black_counter > white_counter)
    return BLACK_WIN;
  else if (black_counter < white_counter)
    return WHITE_WIN;
  else
    return DRAW;
}

/* Check the Validility of the Movement */
bool GameControl::is_valid_movement(Board_t &__board, Coord_t __pos,
                                    bool is_black) {
  /* Cornor is not valid */
  if (__board[__pos.first][__pos.second] == ILLEGAL) return false;
  /* Has been occupied is also not valid */
  if (__board[__pos.first][__pos.second] != UNOCCUPIED) return false;
  /* Inside safe area, no need check */
  if (__pos.first >= 1 && __pos.first <= 6 && __pos.second >= 1 &&
      __pos.second <= 6)
    return true;

  /*
      [B]    [W]     [...][B]
      [start][middle][...][end]
  */
  int middle_color = (is_black) ? WHITE : BLACK;
  int end_color    = (is_black) ? BLACK : WHITE;

  /* Eight Directions */
  for (int i = 0; i < 8; i++) {
    /* Reset */
    int cur_r = __pos.first;
    int cur_c = __pos.second;
    int state = 0;

    /* Step out */
    cur_r += direction[i].first;
    cur_c += direction[i].second;

    /* Check */
    while (is_in_bound(Coord_t(cur_r, cur_c))) {
      if (state == 0 && __board[cur_r][cur_c] == middle_color) {
        /* [B][W] */
        state = 1;
      } else if (state == 1 && __board[cur_r][cur_c] == middle_color) {
        /* [B][W][...] */
        state = 1;
      } else if (state == 1 && __board[cur_r][cur_c] == end_color) {
        /* [B][W][...][B] */
        return true;
      } else {
        /* Other Fail Situation */
        break;
      }

      /* Step Out */
      cur_r += direction[i].first;
      cur_c += direction[i].second;
    }
  }

  /* Fail */
  return false;
}

/* Check Whether this coord is in board or not */
bool GameControl::is_in_bound(Coord_t __pos) {
  int __r = __pos.first;
  int __c = __pos.second;
  return (__r >= 0) && (__r < HEIGHT) && (__c >= 0) && (__c < WIDTH);
}

/* Check Whether this Board is at terminatino state */
bool GameControl::is_end(Board_t &__board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (is_valid_movement(__board, Coord_t(i, j), true) ||
          is_valid_movement(__board, Coord_t(i, j), false))
        return false;
    }
  }
  return true;
}

/* Class: UCT_Node */
class UCT_Node {
 public:
  Vertex_t         parent;
  vector<Vertex_t> childs;

  State_t  state;   // Board of This Node
  Action_t action;  // The Last Piece's Coordinate
  Color_t  color;   // The Last Piece's Color

  vector<Coord_t> valid_next_act;  // Valid position for this state.

  unsigned long long n, q;

 public:
  UCT_Node(Vertex_t, State_t &, Action_t, Color_t);
  bool is_expandable();
  void update_valid_next_act();
};

UCT_Node::UCT_Node(Vertex_t __parent, State_t &__state, Action_t __action,
                   Color_t __color) {
  this->parent = __parent;
  this->childs.clear();

  this->state  = __state;
  this->action = __action;
  this->color  = __color;

  this->update_valid_next_act();

  this->n = 0;
  this->q = 0;
}

bool UCT_Node::is_expandable() {
  return (this->valid_next_act.size() != this->childs.size());
}

void UCT_Node::update_valid_next_act() {
  bool is_next_black   = (this->color == BLACK) ? false : true;
  this->valid_next_act = GameControl::get_valid_pos(this->state, is_next_black);

  /* There is no possible action, pass */
  if (this->valid_next_act.empty()) this->valid_next_act.push_back(NO_ACTION);
}

/* Class: UCT_Tree */
class UCT_Tree {
 public:
  int      id;
  Vertex_t root;

 public:
  UCT_Tree(int __id) {
    this->id   = __id;
    this->root = NULL;
    srand(time(NULL));
  }
  Action_t uct_search(State_t, Color_t);
  Vertex_t tree_policy(Vertex_t);
  Vertex_t expand(Vertex_t);
  Vertex_t best_child(Vertex_t, const double);
  Result_t default_policy(State_t, Color_t);
  void     backup(Vertex_t, Result_t);
  void     clear() { this->root = NULL; }
} uct(1), uct2(2);

/* Search, (__color is the Last Piece's Color) */
Action_t UCT_Tree::uct_search(State_t __s0, Color_t __color) {
  if (this->root == NULL) {
    /* Create root node V0 by State S0 */
    this->root = new UCT_Node(NULL, __s0, NO_ACTION, __color);
  } else {
    bool matched = false;
    for (Vertex_t child : this->root->childs) {
      if (child->state == __s0) {
        /* Replace */
        this->root         = child;
        this->root->parent = NULL;
        matched            = true;
        break;
      }
    }
    if (!matched) {
      /* Create root node V0 by State S0 */
      this->root = new UCT_Node(NULL, __s0, NO_ACTION, __color);
    }
  }

  /* Run */
  clock_t start = clock();
  clock_t end   = clock();
  while ((int)(end - start) < 475000) {
    UCT_Node *V1    = this->tree_policy(this->root);
    Result_t  delta = this->default_policy(V1->state, V1->color);
    this->backup(V1, delta);
    end = clock();
  }

  /* Get Best Child and Replace the Root */
  Vertex_t best      = this->best_child(this->root, 0);
  this->root         = best;
  this->root->parent = NULL;

  return best->action;
}

/* Tree Policy */
Vertex_t UCT_Tree::tree_policy(Vertex_t __v) {
  while (!GameControl::is_end(__v->state)) {
    if (__v->is_expandable()) {
      return this->expand(__v);
    } else {
      __v = this->best_child(__v, sqrt(2));
    }
  }
  return __v;
}

/* Epxand */
Vertex_t UCT_Tree::expand(Vertex_t __v) {
  /* Find Unchoosed Actions */
  vector<Action_t> unchoosed_action;
  unchoosed_action.clear();

  /* Do Matching */
  for (Action_t action : __v->valid_next_act) {
    bool is_in_child_list = false;

    for (Vertex_t child : __v->childs) {
      if (action == child->action) {
        is_in_child_list = true;
        break;
      }
    }

    if (!is_in_child_list) unchoosed_action.push_back(action);
  }

  /* CHoose an Action from Unchoosed Action */
  int idx = rand() % unchoosed_action.size();

  /* Do it and Create new UCT_Node */
  Action_t new_action = unchoosed_action[idx];
  Color_t  new_color  = (__v->color == BLACK) ? WHITE : BLACK;
  State_t  new_state  = __v->state;
  GameControl::set_and_flip(new_state, new_action,
                            (new_color == BLACK) ? true : false);

  Vertex_t new_child = new UCT_Node(__v, new_state, new_action, new_color);
  __v->childs.push_back(new_child);

  return new_child;
}

/* Best Child */
Vertex_t UCT_Tree::best_child(Vertex_t __v, const double __c) {
  double   max  = -10e9;
  Vertex_t best = NULL;
  for (Vertex_t child : __v->childs) {
    double ucb =
        1.0 * child->q / child->n + __c * sqrt(1.0 * log(__v->n) / child->n);

    if (child->action != NO_ACTION) {
      // ucb *= (weight[child->action.first * 8 + child->action.second] +100.0);
      // ucb *= weight2[child->action.first * 8 + child->action.second];
      // ucb *= weight3[child->action.first * 8 + child->action.second];
      if (id == 1)
        ucb *= weight4[child->action.first * 8 + child->action.second];
      if (id == 2)
        ucb *= weight4_2[child->action.first * 8 + child->action.second];
    }

    if (ucb > max) {
      max  = ucb;
      best = child;
    }
  }
  return best;
}

/* Default Policy (__color is the Last Piece's Color) */
Result_t UCT_Tree::default_policy(State_t __state, Color_t __color) {
  /* Reverse it for next player */
  bool is_black = (__color == BLACK) ? false : true;

  /* Random Play */
  while (!GameControl::is_end(__state)) {
    vector<Action_t> possible_act =
        GameControl::get_valid_pos(__state, is_black);

    Action_t act;
    if (possible_act.size() == 0) {
      act = NO_ACTION;
    } else {
      act = possible_act[rand() % possible_act.size()];
      GameControl::set_and_flip(__state, act, is_black);
    }

    is_black = (is_black) ? false : true;
  }

  return GameControl::get_result(__state);
}

/* Backup */
void UCT_Tree::backup(Vertex_t __v, Result_t __delta) {
  while (__v != NULL) {
    __v->n++;

    if (__v->color == BLACK && __delta == BLACK_WIN ||
        __v->color == WHITE && __delta == WHITE_WIN) {
      __v->q++;
    }

    __v = __v->parent;
  }
}