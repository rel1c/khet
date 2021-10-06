#include "board.h"

namespace khet {

Board::squares_red = init_bitboard(
  std::vector<int> {a1, a2, a3, a4, a5, a6, a7, a8, i1, i8}
);

Board::squares_silver = init_bitboard(
  std::vector<int> {b1, b8, j1, j2, j3, j4, j5, j6, j7, j8}
);

} // namespace khet
