#include <uct.h>

/*
  Constructor of UCT::Node
*/
UCT::Node::Node(Node *_parent, State &_state, Coord _step, bool _is_black) {
  this->parent = _parent;
  this->childs.clear();

  this->state    = _state;
  this->step     = _step;
  this->is_black = _is_black;
  this->update_valid_next_steps();

  this->n = 0;
  this->q = 0;
}

/*
  Is this node is expandable
  Which means that the child number is less than possible action.
*/
bool UCT::Node::is_expandable(){
  return (this->valid_next_steps.size()) > (this->childs.size());
}

/*
  Update the possible next steps
  If there is no possible next step for this State,
  We will add NO_ACTION as only possible step
*/
void UCT::Node::update_valid_next_steps(){
  /* Decide next steps's color, the inverse of current state's color */
  bool is_next_black = (this->is_black) ? false : true;
}