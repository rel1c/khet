#include <iostream>
#include "move.h"

#define MOVE_TO_INT(a) *(unsigned int *) &a

namespace khet {

const Move Move::_empty_move;

Move::Move() {
  *this = _empty_move;
}

Move::Move(Square from, Square to, bool swap) {
  *this = _empty_move;
  _legal = 1;
  _from = from;
  _to = to;
  _swap = (swap) ? 1 : 0;
}

Move::Move(Square from, Rotation rotation) {
  *this = _empty_move;
  _legal = 1;
  _rotate = 1;
  _from = from;
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

void Move::display() const {
  //TODO
}

std::ostream& operator<<(std::ostream& os, const Move& mov) {
  return os
    << mov._legal << ":"
    << mov._swap << ":"
    << mov._rotate << ":"
    << mov._from << ":"
    << mov._to << ":"
    << mov._rotation << ":"
    << mov._spare;
}

} // namespace khet
