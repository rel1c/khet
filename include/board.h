#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>
#include "bitboard.h"

namespace khet {

enum Color {
  RED,
  SILVER,
};

const std::array<std::string, 2> colorStrings {
  "RED",
  "SILVER",
};

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

const std::array<std::string, 5> pieceStrings {
  "ANUBIS",
  "PHARAOH",
  "PYRAMID",
  "SCARAB",
  "SPHINX"
};

enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

const std::array<std::string, 5> directionStrings {
  "NORTH",
  "EAST",
  "SOUTH",
  "WEST"
};

enum Layout {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

class Board {
public:
  Board();
  Board(Layout);

  static const std::array<std::vector<Square>, NSQUARES> moves_sqrs_;
  static const std::array<Bitboard, NSQUARES> moves_;

  static const Bitboard squares_red_; //TODO enforce with separate look-up tables
  static const Bitboard squares_silver_; //TODO ^^^

  static const Bitboard empty_;
  static const Bitboard full_;

  static const Bitboard sphinx_;

  Bitboard red_;
  Bitboard silver_;

  Bitboard north_;
  Bitboard east_;
  Bitboard south_;
  Bitboard west_;

  Bitboard anubis_;
  Bitboard pharaoh_;
  Bitboard pyramid_;
  Bitboard scarab_;
};

} // namespace khet

#endif
