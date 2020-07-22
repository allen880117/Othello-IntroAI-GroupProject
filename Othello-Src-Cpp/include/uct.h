#pragma once
#include <board.h>
#include <coord.h>
#include <vector>

namespace UCT {
/* Type Define */
typedef Board State;

/* Class: Node of UCT */
class Node {
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

};  // namespace UCT
