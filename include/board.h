#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>
#include "bitboard.h"

namespace khet {

enum class Color : unsigned int {
  RED = 100,
  SILVER = 200,
};

const std::map<Color, std::string> colorStrings {
  {RED, "RED"},
  {SILVER, "SILVER"}
};

enum class Piece : unsigned int {
  ANUBIS = 10,
  PHARAOH = 20,
  PYRAMID = 30,
  SCARAB = 40,
  SPHINX = 50
};

const std::map<Piece, std::string> pieceStrings {
  {ANUBIS, "ANUBIS"},
  {PHARAOH, "PHARAOH"},
  {PYRAMID, "PYRAMID"},
  {SCARAB, "SCARAB"},
  {SPHINX, "SPHINX"}
};

enum class Direction : unsigned int {
  NORTH = 1,
  EAST = 2,
  SOUTH = 3,
  WEST = 4
};

const std::map<Direction, std::string> directionStrings {
  {NORTH, "NORTH"},
  {EAST, "EAST"},
  {SOUTH, "SOUTH"},
  {WEST, "WEST"}
};

enum class Layout : unsigned int {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

enum PieceCode {
  RED_ANUBIS_NORTH = RED + ANUBIS + NORTH,
  RED_ANUBIS_EAST = RED + ANUBIS + EAST,
  RED_ANUBIS_SOUTH = RED + ANUBIS + SOUTH,
  RED_ANUBIS_WEST = RED + ANUBIS + WEST,
  RED_PHARAOH_NORTH = RED + PHARAOH + NORTH,
  RED_PHARAOH_EAST = RED + PHARAOH + EAST,
  RED_PHARAOH_SOUTH = RED + PHARAOH + SOUTH,
  RED_PHARAOH_WEST = RED + PHARAOH + WEST,
  RED_PYRAMID_NORTH = RED + PYRAMID + NORTH,
  RED_PYRAMID_EAST = RED + PYRAMID + EAST,
  RED_PYRAMID_SOUTH = RED + PYRAMID + SOUTH,
  RED_PYRAMID_WEST = RED + PYRAMID + WEST,
  RED_SCARAB_NORTH = RED + SCARAB + NORTH,
  RED_SCARAB_EAST = RED + SCARAB + EAST,
  RED_SCARAB_SOUTH = RED + SCARAB + SOUTH,
  RED_SCARAB_WEST = RED + SCARAB + WEST,
  RED_SPHINX_NORTH = RED + SPHINX + NORTH,
  RED_SPHINX_EAST = RED + SPHINX + EAST,
  RED_SPHINX_SOUTH = RED + SPHINX + SOUTH,
  RED_SPHINX_WEST = RED + SPHINX + WEST,
  SILVER_ANUBIS_NORTH = SILVER + ANUBIS + NORTH,
  SILVER_ANUBIS_EAST = SILVER + ANUBIS + EAST,
  SILVER_ANUBIS_SOUTH = SILVER + ANUBIS + SOUTH,
  SILVER_ANUBIS_WEST = SILVER + ANUBIS + WEST,
  SILVER_PHARAOH_NORTH = SILVER + PHARAOH + NORTH,
  SILVER_PHARAOH_EAST = SILVER + PHARAOH + EAST,
  SILVER_PHARAOH_SOUTH = SILVER + PHARAOH + SOUTH,
  SILVER_PHARAOH_WEST = SILVER + PHARAOH + WEST,
  SILVER_PYRAMID_NORTH = SILVER + PYRAMID + NORTH,
  SILVER_PYRAMID_EAST = SILVER + PYRAMID + EAST,
  SILVER_PYRAMID_SOUTH = SILVER + PYRAMID + SOUTH,
  SILVER_PYRAMID_WEST = SILVER + PYRAMID + WEST,
  SILVER_SCARAB_NORTH = SILVER + SCARAB + NORTH,
  SILVER_SCARAB_EAST = SILVER + SCARAB + EAST,
  SILVER_SCARAB_SOUTH = SILVER + SCARAB + SOUTH,
  SILVER_SCARAB_WEST = SILVER + SCARAB + WEST,
  SILVER_SPHINX_NORTH = SILVER + SPHINX + NORTH,
  SILVER_SPHINX_EAST = SILVER + SPHINX + EAST,
  SILVER_SPHINX_SOUTH = SILVER + SPHINX + SOUTH,
  SILVER_SPHINX_WEST = SILVER + SPHINX + WEST
};

class Board {
public:
  Board();
  Board(Layout);

  PieceCode getPieceAt(Square);

  static const std::array<std::vector<Square>, NSQUARES> moves_sqrs_;
  static const std::array<Bitboard, NSQUARES> moves_;

  static const Bitboard squares_red_; //TODO enforce with separate look-up tables
  static const Bitboard squares_silver_; //TODO ^^^

  static const Bitboard empty_;
  static const Bitboard full_;

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
  Bitboard sphinx_;
};

} // namespace khet

#endif
