#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

namespace khet {

enum Color {
  NO_COLOR = 0,
  RED = 100,
  SILVER = 200,
};

enum Piece {
  NO_PIECE = 0,
  ANUBIS = 10,
  PHARAOH = 20,
  PYRAMID = 30,
  SCARAB = 40,
  SPHINX = 50
};

enum Direction {
  NO_DIRECTION = 0,
  NORTH = 1,
  EAST = 2,
  SOUTH = 3,
  WEST = 4
};

class Board {
public:
  Bitboard getMoves(const Square) const;
  Bitboard getSquaresRed() const;
  Bitboard getSquaresSilver() const;
  Bitboard getPosition(Color, Piece, Direction) const;
private:
  static const std::vector<Bitboard> moves_;

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

} // namespace khet

#endif
