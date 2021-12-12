#include <iostream>
#include "action.h"

#define ACTION_TO_INT(a) *(unsigned int *) &a

namespace khet {

static const Action empty_action;

Action::Action() {
  *this = empty_action;
}

Action::Action(Square from, Square to, bool swap) {
  *this = empty_action;
  this->legal = 1;
  this->from = from;
  this->to = to;
  this->swap = (swap) ? 1 : 0;
}

Action::Action(Square from, Direction dir_old, Direction dir_new) {
  *this = empty_action;
  this->legal = 1;
  this->from = from;
  this->dir_old = dir_old;
  this->dir_new = dir_new;
  this->rotate = 1;
}

bool Action::operator==(const Action& rhs) const {
  return ACTION_TO_INT(*this) == ACTION_TO_INT(rhs);
}

void Action::print() const {
  std::cout << "displayAction not implemented" << std::endl;
  //<< "swap:" << act.swap_
  //<< ",rotate:" << rotationStrings.at(act.rotate_)
  //<< ",from:" << squareStrings[act.from_]
  //<< ",to:" << squareStrings[act.to_]
  //<< ",direction:" << directionStrings.at(act.direction_)
  //<< "}";
}

std::ostream& operator<<(std::ostream& os, const Action& act) {
  return os //TODO make this more readable
    << act.legal << ":"
    << act.from << ":"
    << act.to << ":"
    << act.dir_old << ":"
    << act.dir_new << ":"
    << act.swap << ":"
    << act.spare << ":"
    << act.rotate;
}

} // namespace khet
