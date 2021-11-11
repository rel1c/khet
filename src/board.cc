#include "board.h"

namespace khet {

Board::bb_squares_red = initBitboard(
  std::vector<int> {A1, A2, A3, A4, A5, A6, A7, A8, I1, I8}
);

Board::bb_squares_silver = initBitboard(
  std::vector<int> {B1, B8, J1, J2, J3, J4, J5, J6, J7, J8}
);

const std::array<Bitboard, NFILES * NRANKS> Board::moves_ {
  bool right, left, top, bottom;
  std::vector<Square> squares;
  for (int i = 0; i < moves_.length(); i++) {
    if (i - 1 % NFILES == 0) {
      right = true;
    }
    else if (i % NFILES == 0) {
      left = true;
    }
    if (i + NFILES >= NFILES * NRANKS) {
      top = true;
    }
    else if (i - NFILES < 0) {
      bottom = true;
    }

    if (!top && !left) {

    }
  }
}

} // namespace khet
