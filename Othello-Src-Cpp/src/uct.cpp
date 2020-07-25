#include <game_util.h>
#include <uct.h>

#include <cstdlib>
#include <ctime>
#include <limits>

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
  this->weight_black.reset();
  this->weight_white.reset();
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

/*
  Expand Node (that is not full-expanded)
*/
UCT::Node *UCT::Tree::expand(UCT::Node *_v) {
  /* Find Unchoosed Steps */
  std::vector<Coord> unchoosed_steps;
  unchoosed_steps.clear();

  /* Do Matching, Find unused next-steps */
  for (Coord step : _v->valid_next_steps) {
    /* Is this step has been expanded (It has been a child) */
    bool is_in_child_list = false;

    /* Search among childs */
    for (Node *child : _v->childs) {
      /* This Step already been expanded */
      if (step == child->step) {
        is_in_child_list = true;
        break;
      }
    }

    /* This Step hasn't been expanded yet */
    if (!is_in_child_list) unchoosed_steps.push_back(step);
  }

  /* Choose a step from unchoosed next steps */
  int idx = rand() % unchoosed_steps.size();

  /* Do the step */
  Coord new_step           = unchoosed_steps.at(idx);
  bool  is_new_color_black = (_v->is_black) ? false : true;
  State new_state          = _v->state;
  GameUtil::do_set_and_flip(new_state, is_new_color_black, new_step);

  /* Create & Push new child into child list */
  UCT::Node *new_child =
      new UCT::Node(_v, new_state, new_step, is_new_color_black);
  _v->childs.push_back(new_child);

  /* Return this new child */
  return new_child;
}

/*
  Return Best Child
  We use UCB and Weight here to choose best one
  Calculate the Score of each Child, and Pick Best one
*/
UCT::Node *UCT::Tree::best_child(UCT::Node *_v, const double _c) {
  /* max value for picking best child */
  double     max  = std::numeric_limits<double>::max();
  UCT::Node *best = NULL;

  /* Calculate the Score of each Child, and Pick Best one */
  for (UCT::Node *child : _v->childs) {
    /* Calculate UCB */
    double ucb =
        1.0 * child->q / child->n + _c * sqrt(1.0 * log(_v->n) / child->n);

    /* Weight */
    if (child->step != NO_ACTION) {
      /* Multiply Weight to ucb according to coordinate of step */
      if (this->root->is_black) {
        // Opponent's Color is Black
        // We are the White one
        ucb *= this->weight_white.get(child->step);
      } else {
        // Opponent's Color is White
        // We are the Black one
        ucb *= this->weight_black.get(child->step);
      }
    }

    /* Compare */
    if (ucb > max) {
      max  = ucb;
      best = child;
    }
  }

  /* Return Best One */
  return best;
}