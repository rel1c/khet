#ifndef ACTION_H_
#define ACTION_H_

namespace khet {

struct Action {
  bool swap_;
  int rotate_; // -1 or 1 : ccw or cw TODO make enum
  Square from_;
  Square to_;
  Direction direction_;
};

} // namespace khet

#endif
