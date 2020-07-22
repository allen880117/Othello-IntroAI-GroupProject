#pragma once
/* Color Definition */
#define B_GREEN_F_BLACK "\033[0;30;42m"
#define B_BLACK "\033[0;40m"
#define B_WHITE "\033[0;47m"
#define NORMAL "\033[0m"
#define CLEAR "\033[2J\033[1;1H"
/* Display */
namespace Display {
void clear();

template <class T>
void print(T &_t);
}  // namespace Display