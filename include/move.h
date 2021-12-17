#ifndef MOVE_H_
#define MOVE_H_

#include <ostream>

#include "util.h"

namespace khet {

class Move {
public:
  Move();

  Move(Square, Square, Piece, bool swap = false);

  Move(Square, Piece, Rotation);

  bool isLegal() const;
  bool isSwap() const;
  bool isRotate() const;

  Square from() const;
  Square to() const;
  Rotation rotation() const;

  bool operator==(const Move& rhs) const;
  bool operator!=(const Move& rhs) const;

  std::string toStr() const;

  friend std::ostream& operator<<(std::ostream&, const Move&);
private:
  unsigned int _legal : 1;
  unsigned int _swap : 1;
  unsigned int _rotate : 1;
  Square _from : 7;
  Square _to : 7;
  Rotation _rotation : 2;
  Piece _piece : 3;
  unsigned int _spare : 9;

  static const Move _empty_move;
};

} // namespace khet

#endif
