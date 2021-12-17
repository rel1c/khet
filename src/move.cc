#include <iostream>
#include "move.h"

#define MOVE_TO_INT(a) *(unsigned int *) &a

namespace khet {

const Move Move::_empty_move;

Move::Move() {
  *this = _empty_move;
}

Move::Move(Square from, Square to, Piece piece, bool swap) {
  *this = _empty_move;
  _legal = 1;
  _from = from;
  _to = to;
  _piece = piece;
  _swap = (swap) ? 1 : 0;
}

Move::Move(Square from, Piece piece, Rotation rotation) {
  *this = _empty_move;
  _legal = 1;
  _rotate = 1;
  _from = from;
  _piece = piece;
  _rotation = rotation;
}

bool Move::isLegal() const {
  return _legal & 0x1;
}

bool Move::isSwap() const {
  return _swap & 0x1;
}

bool Move::isRotate() const {
  return _rotate & 0x1;
}

Square Move::from() const {
  return _from;
}

Square Move::to() const {
  return _to;
}

Rotation Move::rotation() const {
  return _rotation;
}

bool Move::operator==(const Move& rhs) const {
  return MOVE_TO_INT(*this) == MOVE_TO_INT(rhs);
}

bool Move::operator!=(const Move& rhs) const {
  return MOVE_TO_INT(*this) != MOVE_TO_INT(rhs);
}

std::string Move::toStr() const {
  std::string str = "";
  char from = charFromPiece(_piece);
  if (from && from != 'p')
    str += std::toupper(from);
  str += squareStrings[_from];
  if (_rotate && _rotation == POSITIVE)
    str += '>';
  else if (_rotate && _rotation == NEGATIVE)
    str += '<';
  else if (_swap)
    str += 'x' + squareStrings[_to];
  else
    str += ' ' + squareStrings[_to];
  return str;
}

std::ostream& operator<<(std::ostream& os, const Move& m) {
  return os
    << m._legal << ":"
    << m._swap << ":"
    << m._rotate << ":"
    << m._from << ":"
    << m._to << ":"
    << m._rotation << ":"
    << m._piece << ":"
    << m._spare;
}

} // namespace khet
