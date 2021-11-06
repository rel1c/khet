#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

namespace khet {

enum Color {
  RED,
  SILVER,
};

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

class Board {
public:
  Bitboard getMoves(const Square) const;
  Bitboard getSquaresRed() const;
  Bitboard getSquaresSilver() const;
  Bitboard getPosition(Color) const;
  Bitboard getPosition(Color, Piece) const;
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
