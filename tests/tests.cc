#include "bitboard.h"
#include "gamestate.h"

#include <gtest/gtest.h>

#include <iostream>
#include <cstdint>

namespace khet {

/// Bitboard Tests /////////////////////////////////////////////////////////////

class BitboardTest : public::testing::Test {
public:
  void SetUp() { board.bits.reset(); }
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

TEST_F(BitboardTest, StandardOutTest) {
  board = Bitboard(std::bitset<128>(0x00ff00ff00ff00ff) << 64 
                 | std::bitset<128>(0x00ff00ff00ff00ff));
  testing::internal::CaptureStdout();
  std::cout << board;
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output.length(), 128) << "Correct dimensions";
  std::string expect = "00000000111111110000000011111111"
                       "00000000111111110000000011111111"
                       "00000000111111110000000011111111"
                       "00000000111111110000000011111111";
  ASSERT_EQ(expect, output) << "Proper conversion to string";
}

TEST_F(BitboardTest, ElementAccessTest) {
  board.set(9, 7, true);
  EXPECT_EQ(board.bits[79], true) << "Cartesian to bitwise mapping";
  board.set('e', '4', true);
  EXPECT_EQ(board.bits[34], true) << "Alphanumeric to bitwise mapping";
  EXPECT_EQ(board.get(4, 3), true) << "Alphanumeric to Cartesian mapping";
}

TEST_F(BitboardTest, DisplayTest) {
  board = Bitboard(std::bitset<128>(0x0000000000003fc7) << 64 
                 | std::bitset<128>(0xf0fc1f03c0700c01));
  testing::internal::CaptureStdout();
  board.display();
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output.length(), 88) << "Correct dimensions";
  std::string expect = "1111111100\n1111111000\n"
                       "1111110000\n1111100000\n"
                       "1111000000\n1110000000\n"
                       "1100000000\n1000000000\n";
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
/*
TEST_F(GamestateTest, BoardConstantsTest) {
  testing::internal::CaptureStdout();
  Gamestate::squares_red.display();
  std::string output = testing::internal::GetCapturedStdout();
  std::string expect = "1000000010\n1000000000\n"
                       "1000000000\n1000000000\n"
                       "1000000000\n1000000000\n"
                       "1000000000\n1000000010\n";
  EXPECT_EQ(expect, output) << "Red board squares";
  Gamestate::squares_silver.display();
  output = testing::internal::GetCapturedStdout();
  expect = "0100000001\n0000000001\n"
           "0000000001\n0000000001\n"
           "0000000001\n0000000001\n"
           "0000000001\n0100000001\n";
  EXPECT_EQ(expect, output) << "Silver board squares";
  Gamestate::pieces_sphinx.display();
  output = testing::internal::GetCapturedStdout();
  expect = "1000000000\n0000000000\n"
           "0000000000\n0000000000\n"
           "0000000000\n0000000000\n"
           "0000000000\n0000000001\n";
  EXPECT_EQ(expect, output) << "Sphinx board squares";
}
*/
} // namespace khet
