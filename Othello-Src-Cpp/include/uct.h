#pragma once
#include <board.h>
#include <coord.h>
#include <weight.h>

#include <cmath>
#include <vector>

#define COEFF (sqrt(2))

namespace UCT {
/* Type Define */
typedef Board State;

/* Class: Node of UCT */
class Node {
  friend class Tree;

 private:
  Node *              parent;
  std::vector<Node *> childs;

  State              state;             // Board of This Node
  Coord              step;              // The Last Pieces's Coordinate
  bool               is_black;          // The Last Pieces's Color
  std::vector<Coord> valid_next_steps;  // The Valid Next Step for this State

  unsigned long long n;
  unsigned long long q;

 public:
  Node(Node *, State &, Coord, bool);
  bool is_expandable();
  void update_valid_next_steps();
};

/* Class: Tree of UCT */
class Tree {
 private:
  Node * root;
  Weight weight_white;
  Weight weight_black;

 public:
  Tree();
  Coord uct_search(State, bool);
  Node *tree_policy(Node *);
  Node *expand(Node *);
  Node *best_child(Node *, const double);
  int   default_policy(State, bool);
  void  backup(Node *, int);
};
};  // namespace UCT
