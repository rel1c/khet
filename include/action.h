#ifndef ACTION_H_
#define ACTION_H_

#include "board.h"

namespace khet {

enum Rotation {
  NEGATIVE = -1,
  NONE = 0,
  POSITIVE = 1
};

const std::map<Rotation, std::string> rotationStrings {
  {NEGATIVE, "NEGATIVE"},
  {NONE, "NONE"},
  {POSITIVE, "POSITIVE"}
};


struct Action {
  Action();

  bool swap_;
  Rotation rotate_;
  Square from_;
  Square to_;
  Direction direction_;

  void print() const;

  bool operator==(const Action&) const;

  friend std::ostream& operator<<(std::ostream&, const Action&);
};

} // namespace khet

#endif
