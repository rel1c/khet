#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "bitboard.h"

namespace khet {

enum Color {
  RED = 100,
  SILVER = 200,
};

enum Piece {
  ANUBIS = 10,
  PHARAOH = 20,
  PYRAMID = 30,
  SCARAB = 40,
  SPHINX = 50
};

enum Direction {
  NORTH = 1,
  EAST = 2,
  SOUTH = 3,
  WEST = 4
};

enum Layout {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

struct Board {
  static const std::array<Bitboard, NFILES * NRANKS> moves_;

  static const Bitboard squares_red_;
  static const Bitboard squares_silver_;

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

static void initBoard(Board&, Layout);

} // namespace khet

#endif
