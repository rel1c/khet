#include <iostream>
#include "action.h"

namespace khet {

Action::Action() {
  swap_ = false;
  rotate_ = NONE;
  from_ = A1;
  to_ = J8;
  direction_ = NORTH;
}

bool Action::operator==(const Action& rhs) const {
  return swap_ == rhs.swap_
    && rotate_ == rhs.rotate_
    && from_ == rhs.from_
    && to_ == rhs.to_
    && direction_ == rhs.direction_;
}

void Action::print() const {
  std::cout << "displayAction not implemented" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Action& act) {
  return os << "Action{"
    << "swap:" << act.swap_
    << ",rotate:" << rotationStrings.at(act.rotate_)
    << ",from:" << squareStrings[act.from_]
    << ",to:" << squareStrings[act.to_]
    << ",direction:" << directionStrings.at(act.direction_)
    << "}";
}

} // namespace khet
