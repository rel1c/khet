#include "board.h"

namespace khet {

Bitboard Bitboard::getMoves(const Square s) const {
  return empty_;
}

Bitboard Bitboard::getSquaresRed() const {
  return squares_red;
}

Bitboard Bitboard::getSquaresSilver() const {
  return squares_silver;
}

Bitboard Bitboard::getPosition(Color c=NO_COLOR,
                               Piece p=NO_PIECE,
                               Direction d=NO_DIRECTION) const {
  Bitboard bb = full_;
  switch (c) {
  case NO_COLOR:
    goto position;
  case RED:
    bb &= red_;
    break;
  case SILVER:
    bb &= silver_;
    break;
  }
position:
  switch (p) {
  case NO_POSITION:
    goto direction;
  case ANUBIS:
    bb &= anubis_;
    break;
  case PHARAOH:
    bb &= pharaoh_;
    break;
  case PYRAMID:
    bb &= pyramid_;
    break;
  case SCARAB:
    bb &= scarab_;
    break;
  case SPHINX:
    bb &= sphinx_;
    break;
  }
direction:
  switch (d) {
  case NO_DIRECTION:
    break;
  case NORTH:
    bb &= north_;
    break;
  case EAST:
    bb &= east_;
    break;
  case SOUTH:
    bb &= south_;
    break;
  case WEST:
    bb &= west_;
    break;
  }
  return bb;
}

Board::bb_squares_red = initBitboard(
  std::vector<int> {A1, A2, A3, A4, A5, A6, A7, A8, I1, I8}
);

Board::bb_squares_silver = initBitboard(
  std::vector<int> {B1, B8, J1, J2, J3, J4, J5, J6, J7, J8}
);

} // namespace khet
