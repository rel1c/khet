#include "bitboard.h"

namespace khet {

const std::array <bitboard,10> files = {
  init_bitboard(std::vector<int> {a1, a2, a3, a4, a5, a6, a7, a8}),
  init_bitboard(std::vector<int> {b1, b2, b3, b4, b5, b6, b7, b8}),
  init_bitboard(std::vector<int> {c1, c2, c3, c4, c5, c6, c7, c8}),
  init_bitboard(std::vector<int> {d1, d2, d3, d4, d5, d6, d7, d8}),
  init_bitboard(std::vector<int> {e1, e2, e3, e4, e5, e6, e7, e8}),
  init_bitboard(std::vector<int> {f1, f2, f3, f4, f5, f6, f7, f8}),
  init_bitboard(std::vector<int> {g1, g2, g3, g4, g5, g6, g7, g8}),
  init_bitboard(std::vector<int> {h1, h2, h3, h4, h5, h6, h7, h8}),
  init_bitboard(std::vector<int> {i1, i2, i3, i4, i5, i6, i7, i8}),
  init_bitboard(std::vector<int> {j1, j2, j3, j4, j5, j6, j7, j8}),
};

const std::array <bitboard,8> ranks = {
  init_bitboard(std::vector<int> {a1, b1, c1, d1, e1, f1, g1, h1, i1, j1}),
  init_bitboard(std::vector<int> {a2, b2, c2, d2, e2, f2, g2, h2, i2, j2}),
  init_bitboard(std::vector<int> {a3, b3, c3, d3, e3, f3, g3, h3, i3, j3}),
  init_bitboard(std::vector<int> {a4, b4, c4, d4, e4, f4, g4, h4, i4, j4}),
  init_bitboard(std::vector<int> {a5, b5, c5, d5, e5, f5, g5, h5, i5, j5}),
  init_bitboard(std::vector<int> {a6, b6, c6, d6, e6, f6, g6, h6, i6, j6}),
  init_bitboard(std::vector<int> {a7, b7, c7, d7, e7, f7, g7, h7, i7, j7}),
  init_bitboard(std::vector<int> {a8, b8, c8, d8, e8, f8, g8, h8, i8, j8}),
};

bitboard init_bitboard(std::vector<int> v) {
  bitboard bb;
  for (auto& i : v) {
    bb.set(i);
  }
  return bb;
};

} // namespace khet
