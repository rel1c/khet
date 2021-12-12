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

bool Move::operator==(const Move& rhs) const {
  return MOVE_TO_INT(*this) == MOVE_TO_INT(rhs);
}

std::ostream& operator<<(std::ostream& os, const Move& mov) {
  return os //TODO make this more readable
    << mov._legal << ":"
    << mov._swap << ":"
    << mov._rotate << ":"
    << mov._from << ":"
    << mov._to << ":"
    << mov._rotation << ":"
    << mov._spare;
}

} // namespace khet
