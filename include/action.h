#ifndef ACTION_H_
#define ACTION_H_

#include "board.h"

namespace khet {

struct Action {
  unsigned int valid : 1;
  unsigned int from : 7;
  unsigned int to : 7;
  unsigned int dir_old : 2;
  unsigned int dir_new : 2;
  unsigned int swap : 1;
  unsigned int spare : 12;

  Action();

  Action(Square, Square, bool = false);

  bool operator==(const Action& rhs) const;

  void print() const;

  friend std::ostream& operator<<(std::ostream&, const Action&);
};

} // namespace khet

#endif
