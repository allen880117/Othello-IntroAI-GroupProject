#include <game_util.h>
#include <uct.h>
#include <cstdlib>
#include <ctime>

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
bool UCT::Node::is_expandable() {
  return (this->valid_next_steps.size()) > (this->childs.size());
}

/*
  Update the possible next steps
  If there is no possible next step for this State,
  We will add NO_ACTION as only possible step
*/
void UCT::Node::update_valid_next_steps() {
  /* Decide next steps's color, the inverse of current state's color */
  bool is_next_black = (this->is_black) ? false : true;
  this->valid_next_steps =
      GameUtil::get_valid_steps(this->state, is_next_black);

  /* There is no possible action, push NO_ACTION */
  if (this->valid_next_steps.empty())
    this->valid_next_steps.push_back(NO_ACTION);
}

/*
  Constructor
*/
UCT::Tree::Tree() {
  this->root = NULL;
  srand(time(NULL));
}

/*
  Do Search in UCT
  (_is_black is the Last Piece's Color)
*/
Coord UCT::Tree::uct_search(State _s0, bool _is_black) {
  /* Check Root (Try to reuse the result from last time) */
  if (this->root == NULL) {
    /* Root is not existing */
    /* Create root node V0 by State S0 */
    this->root = new UCT::Node(NULL, _s0, NO_ACTION, _is_black);
  } else {
    /* Root is existing */
    /* Try to find node that fit current state, _s0 */
    bool matched = false;
    for (Node *child : this->root->childs) {
      if (child->state == _s0) {
        /* Replace root */
        this->root         = child;
        this->root->parent = NULL;
        matched            = true;
        break;
      }
    }

    /* Can't Find Matched Node */
    if (!matched) {
      /* Create root node V0 by State S0 */
      this->root = new UCT::Node(NULL, _s0, NO_ACTION, _is_black);
    }
  }

  /* Run */
  clock_t start = clock();
  clock_t end   = clock();
  while ((int)(end - start) < 4750) {
    /* the unit of time will change between UNIX and WIN */
    UCT::Node *V1    = this->tree_policy(this->root);
    int        delta = this->default_policy(V1->state, V1->is_black);
    this->backup(V1, delta);
    end = clock();
  }

  /* Get Best Child and Replace the Root */
  Node *best         = this->best_child(this->root, 0);
  this->root         = best;
  this->root->parent = NULL;

  /* Return */
  return best->step;
}

/*
  The Policy of the Tree
*/
UCT::Node *UCT::Tree::tree_policy(UCT::Node *_v) {
  /* The State is not terminated state */
  while (!GameUtil::is_end(_v->state)) {
    if (_v->is_expandable()) {
      /* Expand the Node */
      return this->expand(_v);
    } else {
      /* Pick Best Child */
      return this->best_child(_v, COEFF);
    }
  }
  return _v;
}