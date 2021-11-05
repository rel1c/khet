#include "board.h"

namespace khet {

Board::squares_red = initBitboard(
  std::vector<int> {A1, A2, A3, A4, A5, A6, A7, A8, I1, I8}
);

Board::squares_silver = initBitboard(
  std::vector<int> {B1, B8, J1, J2, J3, J4, J5, J6, J7, J8}
);

} // namespace khet
