#include <cstdint>
#include <iostream>
#include <gtest/gtest.h>
#include "bitboard.h"

namespace khet {

class BitboardTest : public::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}
protected:
  Bitboard board;
};

TEST_F(BitboardTest, BitsetTest) {
  ASSERT_EQ(board.bits.size(), 128);
  board.setAll(true);
  ASSERT_EQ(board.bits.all(), true);
  ASSERT_EQ(board.bits.count(), 128);
  board.setAll(false);
  ASSERT_EQ(board.bits.none(), true);
  ASSERT_EQ(board.bits.count(), 0);
}

TEST_F(BitboardTest, ElementAccessTest) {
  board.setAll(false);
  ASSERT_EQ(board.get(0, 0), false);
  board.bits[0] = true;
  EXPECT_EQ(board.get(0, 0), true);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 10; j++) {
      board.set(i, j, true);
      EXPECT_EQ(board.bits[10*i + j], true);
    }
  }
  board.bits >>= 80;
  EXPECT_EQ(board.bits.count(), 0);
}

} // namespace khet
