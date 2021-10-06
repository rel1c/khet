#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <array>
#include <bitset>
#include <vector>

namespace khet {

using bitboard = std::bitset <128>;

enum square {
  a1, b1, c1, d1, e1, f1, g1, h1, i1, j1,
  a2, b2, c2, d2, e2, f2, g2, h2, i2, j2,
  a3, b3, c3, d3, e3, f3, g3, h3, i3, j3,
  a4, b4, c4, d4, e4, f4, g4, h4, i4, j4,
  a5, b5, c5, d5, e5, f5, g5, h5, i5, j5,
  a6, b6, c6, d6, e6, f6, g6, h6, i6, j6,
  a7, b7, c7, d7, e7, f7, g7, h7, i7, j7,
  a8, b8, c8, d8, e8, f8, g8, h8, i8, j8,
};

extern const std::array <bitboard,10> files;
extern const std::array <bitboard,8> ranks;

bitboard init_bitboard(std::vector<int> v);

} // namespace khet

#endif
