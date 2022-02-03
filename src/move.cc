#include "move.h"
#include <iostream>

void displayMove(Move m) {
  assert(getFrom(m) != SQ_NONE);
  std::string str = "";
  std::string from = SquareStr[getFrom(m)];
  if (isRotate(m)) {
    std::string rotate = (getRotation(m) == POSITIVE) ? "POSITIVE" : "NEGATIVE";
    str += from + ":" + rotate;
    std::cout << str << std::endl;
    return;
  }
  std::string to = SquareStr[getTo(m)];
  str += from + ":" + to;
  if (isSwap(m)) {
    str += ":SWAP";
  }
  std::cout << str << std::endl;
}
