#ifndef PIECE_CODE_H
#define PIECE_CODE_H

#include <ostream>

namespace khet {

enum Color {
  SILVER,
  RED,
};

enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

struct PieceCode {
  Color color;
  Piece piece;
  Direction direction;

  PieceCode(Color, Piece, Direction);

  friend std::ostream& operator<<(std::ostream&, const PieceCode&);
};

} // namespace khet

#endif
