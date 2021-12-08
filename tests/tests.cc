#include "action.h"
#include "bitboard.h"
#include "board.h"
#include "gamestate.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <iostream>
#include <vector>

namespace khet {

/// Bitboard Tests /////////////////////////////////////////////////////////////

class BitboardTest : public::testing::Test {};

/* Test the mapping of bitboard notation to actual indices */
TEST_F(BitboardTest, SquareIndexTest) {
  ASSERT_EQ(A1, 0);
  ASSERT_EQ(J8, 79);
}

/* Test creating initializing a bitboard from a notation vector */
TEST_F(BitboardTest, InitBoardTest) {
  Bitboard bb;
  ASSERT_FALSE(bb.all());
  bb = initBitboard(std::vector<Square> {A1, E5, J8});
  EXPECT_EQ(bb[A1], 1);
  EXPECT_EQ(bb[E5], 1);
  EXPECT_EQ(bb[J8], 1);
}

/* Test the file values */
TEST_F(BitboardTest, FilesTest) {
  std::vector<Bitboard> files = {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E,
                                 FILE_F, FILE_G, FILE_H, FILE_I, FILE_J};
  ASSERT_EQ(NFILES, files.size());
  for (int i = 0; i < NFILES; i++) {
    Bitboard file = files[i];
    for (int j = 0; j < NRANKS; j++) {
      EXPECT_EQ(file[i + j * NFILES], 1);
    }
  }
}

/* Test the rank values */
TEST_F(BitboardTest, RanksTest) {
  std::vector<Bitboard> ranks = {RANK_1, RANK_2, RANK_3, RANK_4,
                                 RANK_5, RANK_6, RANK_7, RANK_8};
  ASSERT_EQ(NRANKS, ranks.size());
  for (int i = 0; i < NRANKS; i ++) {
    Bitboard rank = ranks[i];
    for (int j = 0; j < NFILES; j++) {
      EXPECT_EQ(rank[i * NFILES + j], 1);
    }
  }
}

/* Display the bitboard in a convenient format */
TEST_F(BitboardTest, DisplayTest) {
  Bitboard bb = initBitboard(std::vector<Square> {
    A1, B2, C3, D6, E6, F4, G2, G7, H5, I8, J1, J6
  });
  testing::internal::CaptureStdout();
  displayBitboard(bb);
  std::string output = testing::internal::GetCapturedStdout();
  std::string expect = 
    "0000000010\n"
    "0000001000\n"
    "0001100001\n"
    "0000000100\n"
    "0000010000\n"
    "0010000000\n"
    "0100001000\n"
    "1000000001\n";
  EXPECT_EQ(output, expect);
}

/// Board Tests ////////////////////////////////////////////////////////////////

class BoardTest : public::testing::Test {};

/* Test empty and full bitboards */
TEST_F(BoardTest, EmptyFullTest) {
  Board b;
  for (int i = 0; i < NFILES * NRANKS; i++) {
    ASSERT_EQ(b.empty_[i], 0);
    ASSERT_EQ(b.full_[i], 1);
  }
}

/* Test the mapping of bitboard notation to actual indices */
TEST_F(BoardTest, ConstructorClassicRedTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.red_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000111100\n"
    "0010000000\n"
    "0000000000\n"
    "1000110100\n"
    "1000000100\n"
    "0000001000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSilverTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.silver_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0001000000\n"
    "0010000001\n"
    "0010110001\n"
    "0000000000\n"
    "0000000100\n"
    "0011110001\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicNorthTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.north_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "1000100000\n"
    "0000000100\n"
    "0000000000\n"
    "0000000100\n"
    "0001110001\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicEastTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.east_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000100\n"
    "0000000000\n"
    "0000000000\n"
    "0000010100\n"
    "1000000000\n"
    "0000001000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSouthTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.south_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000111000\n"
    "0010000000\n"
    "0000000000\n"
    "0010000000\n"
    "0000010001\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicWestTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.west_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0001000000\n"
    "0000000001\n"
    "0010100000\n"
    "0000000000\n"
    "0000000000\n"
    "0010000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicAnubisTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.anubis_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000101000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0001010000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicPharaohTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.pharaoh_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000010000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000100000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicPyramidTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.pyramid_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000100\n"
    "0010000000\n"
    "0001000000\n"
    "1010000101\n"
    "1010000101\n"
    "0000001000\n"
    "0000000100\n"
    "0010000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicScarabTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.scarab_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000110000\n"
    "0000110000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSphinxTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.sphinx_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000001\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, GetPieceAtTest) {
  Board b = Board(CLASSIC);
  EXPECT_EQ(b.getPieceAt(A8), RED_SPHINX_SOUTH);
  EXPECT_EQ(b.getPieceAt(C1), SILVER_PYRAMID_WEST);
  EXPECT_EQ(b.getPieceAt(D1), SILVER_ANUBIS_NORTH);
  EXPECT_EQ(b.getPieceAt(E5), RED_SCARAB_NORTH);
  EXPECT_EQ(b.getPieceAt(H8), RED_PYRAMID_EAST);
}

/// Action Tests ///////////////////////////////////////////////////////////////

class ActionTest : public::testing::Test {};

/* Test ... */
TEST_F(ActionTest, OutStreamTest) {
  Action act;
  // impossible values
  act.swap_ = true;
  act.rotate_ = POSITIVE;
  act.from_ = A2;
  act.to_ = J7;
  act.direction_ = SOUTH;
  testing::internal::CaptureStdout();
  std::cout << act;
  std::string output = testing::internal::GetCapturedStdout();
  std::string expect = "Action{swap:1,rotate:POSITIVE,from:A2,to:J7,direction:SOUTH}";
  EXPECT_EQ(output, expect);
}

/// Gamestate Tests ////////////////////////////////////////////////////////////

class GamestateTest : public::testing::Test {
public:
  void SetUp() {
    actions_pass = false;
  }
  bool actions_pass;
};

/* Test ... */
TEST_F(GamestateTest, GenMovesTest) {
  Gamestate gs;
  Board b = gs.getBoard();
  Bitboard red_pieces = b.red_;
  Bitboard vacant = ~(b.red_ | b.silver_);
  gs.genMoves(G3, vacant); // red pyramid south, classic board
  Action mov1, mov2, mov3, mov4, mov5;
  mov1.from_ = G3;
  mov2.from_ = G3;
  mov3.from_ = G3;
  mov4.from_ = G3;
  mov5.from_ = G3;
  mov1.to_ = G4;
  mov2.to_ = F3;
  mov3.to_ = H3;
  mov4.to_ = F2;
  mov5.to_ = G2;
  using namespace testing;
  EXPECT_THAT(gs.getActions(), Contains(mov1));
  EXPECT_THAT(gs.getActions(), Contains(mov2));
  EXPECT_THAT(gs.getActions(), Contains(mov3));
  EXPECT_THAT(gs.getActions(), Contains(mov4));
  EXPECT_THAT(gs.getActions(), Contains(mov5));
}

/* Test ... */
TEST_F(GamestateTest, GenSwapsTest) {
  GTEST_SKIP();
  Gamestate gs;
}

/* Test ... */
TEST_F(GamestateTest, GenRotationsTest) {
  GTEST_SKIP();
  Gamestate gs;
}

/* Test ... */
TEST_F(GamestateTest, GenSphinxActionTest) {
  GTEST_SKIP();
  Gamestate gs;
}

/* Test ... */
TEST_F(GamestateTest, GenActionsTest) {
  if (!actions_pass)
    GTEST_SKIP();
  Gamestate gs;
}

} // namespace khet
