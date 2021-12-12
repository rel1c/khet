#include "board.h"
#include "util.h"

#include <regex>

namespace khet {

Board::Board() {}

Board::Board(std::string pkn) {
  setToPkn(pkn);
}

Board::Board(Layout layout=CLASSIC) {
  setToPkn(layoutToPkn.at(layout));
}

void setToPkn(std::string pkn) {
  //TODO
}

Bitboard Board::getColor(Color c) const {
  if (c == RED)
    return _red;
  else
    return _silver;
}

Bitboard Board::getDirection(Direction d) const {
  if (d == NORTH)
    return _north;
  else if (d == EAST)
    return _east;
  else if (d == SOUTH)
    return _south;
  else
    return _west;
}

Bitboard Board::getPiece(Piece p) const {
  if (p == ANUBIS)
    return _anubis;
  else if (p == PHARAOH)
    return _pharaoh;
  else if (p == PYRAMID)
    return _pyramid;
  else if (p == SCARAB)
    return _scarab;
  else
    return _sphinx;
}

const Bitboard Board::_red_sqrs = initBitboard(Squares {
  A1, A2, A3, A4, A5, A6, A7, A8, I1, I8
});

const Bitboard Board::_silver_sqrs = initBitboard(Squares {
  B1, B8, J1, J2, J3, J4, J5, J6, J7, J8
});

const Bitboard Board::_empty = 0;

const Bitboard Board::_full = initBitboard(Squares {
  A1, A2, A3, A4, A5, A6, A7, A8,
  B1, B2, B3, B4, B5, B6, B7, B8,
  C1, C2, C3, C4, C5, C6, C7, C8,
  D1, D2, D3, D4, D5, D6, D7, D8,
  E1, E2, E3, E4, E5, E6, E7, E8,
  F1, F2, F3, F4, F5, F6, F7, F8,
  G1, G2, G3, G4, G5, G6, G7, G8,
  H1, H2, H3, H4, H5, H6, H7, H8,
  I1, I2, I3, I4, I5, I6, I7, I8,
  J1, J2, J3, J4, J5, J6, J7, J8,
});

const Bitboard Board::_sphinx = initBitboard(Squares {
  A8, J1
});

} // namespace khet
