#include "board.h"

#ifndef UTIL_H_
#define UTIL_H_

namespace khet {

const std::array<std::string, 2> colorStrings {
  "RED",
  "SILVER",
};

const std::array<std::string, 5> pieceStrings {
  "ANUBIS",
  "PHARAOH",
  "PYRAMID",
  "SCARAB",
  "SPHINX"
};

const std::array<std::string, 5> directionStrings {
  "NORTH",
  "EAST",
  "SOUTH",
  "WEST"
};


} // namespace khet

#endif
