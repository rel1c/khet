#include "bitboard.h"
#include "gamestate.h"

#include <gtest/gtest.h>

#include <iostream>
#include <cstdint>

namespace khet {

/// Bitboard Tests /////////////////////////////////////////////////////////////

class BitboardTest : public::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}
protected:
  Bitboard board;
};

TEST_F(BitboardTest, BitsetTest) {
  ASSERT_EQ(board.size(), 128) << "128b set size";
  board.set();
  ASSERT_EQ(board.all(), true);
  ASSERT_EQ(board.count(), 128) << "Bits set to true";
  board.reset();
  ASSERT_EQ(board.none(), true);
  ASSERT_EQ(board.count(), 0) << "Bits set to false";
}

TEST_F(BitboardTest, ElementAccessTest) {
  Bitlogic::set(board, 9, 7, true);
  EXPECT_EQ(board[79], true) << "Cartesian to bitwise mapping";
  Bitlogic::set(board, 'e', '4', true);
  EXPECT_EQ(board[34], true) << "Alphanumeric to bitwise mapping";
  EXPECT_EQ(Bitlogic::get(board, 4, 3), true) << "Alphanumeric to Cartesian mapping";
}

TEST_F(BitboardTest, DisplayTest) {
  board = Bitboard(0x0000000000003fc7) << 64 | Bitboard(0xf0fc1f03c0700c01);
  testing::internal::CaptureStdout();
  Bitlogic::display(board);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output.length(), 117) << "Correct dimensions";
  std::string expect = "8 1111111100\n7 1111111000\n6 1111110000\n"
                       "5 1111100000\n4 1111000000\n3 1110000000\n"
                       "2 1100000000\n1 1000000000\n  abcdefghij\n";
  EXPECT_EQ(expect, output) << "Properly displayed as gameboard";
}

/// Gamestate Tests ////////////////////////////////////////////////////////////

class GamestateTest : public::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}
protected:
  Gamestate gamestate;
};

} // namespace khet
