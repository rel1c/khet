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
  ASSERT_TRUE(board.all());
  ASSERT_EQ(board.count(), 128) << "Bits set to true";
  board.reset();
  ASSERT_TRUE(board.none());
  ASSERT_EQ(board.count(), 0) << "Bits set to false";
}

TEST_F(BitboardTest, ElementAccessTest) {
  board[32] = true;
  board[75] = true;
  EXPECT_TRUE(Bitlogic::Get(board, 2, 3)) << "Cartesian mapping";
  EXPECT_TRUE(Bitlogic::Get(board, 5, 7)) << "Cartesian mapping";
  EXPECT_TRUE(Bitlogic::Get(board, 'c', '4')) << "Alphanumeric mapping";
  EXPECT_TRUE(Bitlogic::Get(board, 'f', '8')) << "Alphanumeric mapping";
}

TEST_F(BitboardTest, DisplayTest) {
  board = Bitboard(0x0000000000003fc7) << 64 | Bitboard(0xf0fc1f03c0700c01);
  testing::internal::CaptureStdout();
  Bitlogic::Display(board);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output.length(), 117) << "Correct dimensions";
  std::string expect = "8 1111111100\n7 1111111000\n6 1111110000\n"
                       "5 1111100000\n4 1111000000\n3 1110000000\n"
                       "2 1100000000\n1 1000000000\n  abcdefghij\n";
  EXPECT_EQ(expect, output) << "Properly displayed as gameboard";
}

TEST_F(BitboardTest, CreateBoardTest) {
  std::vector<std::string> coords = {"b1", "i1", "b8", "i8"};
  board = Bitlogic::CreateBoard(coords);
  Bitboard expect = Bitboard(
    "0100000010"
    "0000000000"
    "0000000000"
    "0000000000"
    "0000000000"
    "0000000000"
    "0000000000"
    "0100000010"
  );
  EXPECT_EQ(board, expect);
}

/// Gamestate Tests ////////////////////////////////////////////////////////////

class GamestateTest : public::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}
protected:
  Gamestate gamestate;
};

TEST_F(GamestateTest, ConstantBoardTest) {
  std::string expect, output;
  testing::internal::CaptureStdout();
  Bitlogic::Display(gamestate.RedSquares());
  output = testing::internal::GetCapturedStdout();
  expect = "8 1000000010\n7 1000000000\n6 1000000000\n"
           "5 1000000000\n4 1000000000\n3 1000000000\n"
           "2 1000000000\n1 1000000010\n  abcdefghij\n";
  EXPECT_EQ(expect, output) << "Red board squares";
  testing::internal::CaptureStdout();
  Bitlogic::Display(gamestate.SilverSquares());
  output = testing::internal::GetCapturedStdout();
  expect = "8 0100000001\n7 0000000001\n6 0000000001\n"
           "5 0000000001\n4 0000000001\n3 0000000001\n"
           "2 0000000001\n1 0100000001\n  abcdefghij\n";
  EXPECT_EQ(expect, output) << "Silver board squares";
}

} // namespace khet
