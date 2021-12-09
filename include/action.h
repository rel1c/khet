#ifndef ACTION_H_
#define ACTION_H_

#include "board.h"

namespace khet {

struct Action {
  unsigned int legal : 1;
  unsigned int from : 7;
  unsigned int to : 7;
  unsigned int dir_old : 2;
  unsigned int dir_new : 2;
  unsigned int swap : 1;
  unsigned int rotate : 1;
  unsigned int spare : 11;

  Action();

  Action(Square, Square, bool = false);

  Action(Square, Direction, Direction);

  bool operator==(const Action& rhs) const;

  void print() const;

  friend std::ostream& operator<<(std::ostream&, const Action&);
};

} // namespace khet

#endif
