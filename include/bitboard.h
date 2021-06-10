/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <bitset>
#include <cassert>

namespace khet {

struct Bitboard {
  std::bitset<128> bits;

  // Access square of board
  bool get(int x, int y) {
    assert(0 <= x && x <= 7);
    assert(0 <= y && y <= 9);
    return bits[10*y + x];
  }

  // Assign square of board
  void set(int x, int y, bool val) {
    assert(0 <= x && x <= 7);
    assert(0 <= y && y <= 9);
    bits[10*x + y] = val;
  }

  // Set board to all true or false
  void setAll(bool val) {
    if (val)
      bits.set();
    else
      bits.reset();
  }
};

} // namespace khet

#endif
