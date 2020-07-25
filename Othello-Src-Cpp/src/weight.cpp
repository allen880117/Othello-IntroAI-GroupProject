#include <weight.h>

/*
    Default Constructor
*/
Weight::Weight() { this->reset(); }

/*
    Reset the value of weight
*/
void Weight::reset() {
  for (int r = 0; r < BOARD_H; r++) {
    for (int c = 0; c < BOARD_W; c++) {
      this->weight.at(r).at(c) = 1.0;
    }
  }
}

/*
    Set Weight
*/
void Weight::set(int _r, int _c, double _value) {
  this->weight.at(_r).at(_c) = _value;
}

/*
    Set Weight
*/
void Weight::set(Coord _step, double _value) {
  this->set(_step.first, _step.second, _value);
}

/*
    Get Weight
*/
double Weight::get(int _r, int _c) { return this->weight.at(_r).at(_c); }

/*
    Get Weiht
*/
double Weight::get(Coord _step) { return this->get(_step.first, _step.second); }