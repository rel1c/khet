/**
 * @file bitboard.cc
 */

#include "bitboard.h"

namespace khet {

const Bitboard Bitlogic::board_empty = Bitboard(0);
const Bitboard Bitlogic::board_full = Bitboard(~board_empty);

Bitboard Bitlogic::CreateBoard(std::vector<std::string> coords) {
  Bitboard board;
  for (auto coord : coords) {
    assert(coord.length() == 2);
    Bitlogic::Set(board, coord[0], coord[1], 1);
  }
  return board;
}

void Bitlogic::Display(const Bitboard& board) {
  for (int i = ROWS-1; i >= 0; i--) {
    std::cout << i+1 << " ";
    for (int j = 0; j < COLS; j++) {
      char ch = (board[i*COLS + j]) ? '1' : '0';
      std::cout << ch;
    }
    std::cout << "\n";
  }
  std::cout << "  abcdefghij" << std::endl;
}

} // namespace khet
