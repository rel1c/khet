#ifndef MOVE_H_
#define MOVE_H_

namespace khet {

struct Move {
  bool swap_;
  bool rotate_;
  Square from_;
  Square to_;
  Direction direction_;
};

} // namespace khet

#endif
