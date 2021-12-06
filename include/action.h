#ifndef ACTION_H_
#define ACTION_H_

namespace khet {

enum Rotation {
  NEGATIVE = -1,
  NONE = 0,
  POSITIVE = 1
};

struct Action {
  bool swap_;
  Rotation rotate_; // -1 or 1 : ccw or cw TODO make enum
  Square from_;
  Square to_;
  Direction direction_;
};

} // namespace khet

#endif
