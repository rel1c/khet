#include <cstdint>
#include <iostream>
#include <gtest/gtest.h>
#include "bitboard.h"

namespace khet {

class BitboardTest : public::testing::Test {
public:
  void SetUp() {
    board_empty = 0;
    board_full = (__int128) (-1);
  }

  void TearDown() {}
protected:
  Bitboard board;
  Bitboard board_empty;
  Bitboard board_full;
};

TEST_F(BitboardTest, IndexTest) {
  ASSERT_EQ(board_empty[0], 0);
  ASSERT_EQ(board_empty[127], 0);
  ASSERT_EQ(board_full[0], 1);
  ASSERT_EQ(board_full[127], 1);
  board = 1;
  ASSERT_EQ(board[0], 1);
  for (uint8_t i = 0; i < 128; i++) {
    ASSERT_EQ(board[i], 1);
    board.b = board.b << 1;
  }
}

} // namespace khet
