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

const std::map<Layout, std::string> layoutToPkn {
  {
    CLASSIC,
    "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0"
  },
  {
    DYNASTY,
    "3PAP3X/4R5/3SAP3P/3p1p1S1P/p1s1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0"
  },
  {
    IMHOTEP,
    "2SARA3X/0/3P2p3/pP2Sp2pP/pP2Ps2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0"
  },
};

Direction directionFromChar(char);

Piece pieceFromChar(char);

char charFromDirection(Direction);

char charFromPiece(Piece);

} // namespace khet

#endif
