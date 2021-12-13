#ifndef MOVE_H_
#define MOVE_H_

#include <ostream>

#include "board.h"

namespace khet {

class Move {
public:
  Move();

  Move(Square, Square, bool swap = false);

  Move(Square, Rotation);

  bool operator==(const Move& rhs) const;

  friend std::ostream& operator<<(std::ostream&, const Move&);
private:
  unsigned int _legal : 1;
  unsigned int _swap : 1;
  unsigned int _rotate : 1;
  Square _from : 7;
  Square _to : 7;
  Rotation _rotation : 2;
  unsigned int _spare : 13;

  static const Move _empty_move;
};

} // namespace khet

#endif
