#include "bitboard.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>

namespace khet {

/// Bitboard Tests /////////////////////////////////////////////////////////////

class BitboardTest : public::testing::Test {};

TEST_F(BitboardTest, SquareIndexTest) {
  ASSERT_EQ(a1, 0);
  ASSERT_EQ(j8, 79);
}

TEST_F(BitboardTest, FilesTest) {
  ASSERT_EQ(files[0][a1], 1);
  ASSERT_EQ(files[0][a2], 1);
  ASSERT_EQ(files[0][a3], 1);
  ASSERT_EQ(files[0][a4], 1);
  ASSERT_EQ(files[0][a5], 1);
  ASSERT_EQ(files[0][a6], 1);
  ASSERT_EQ(files[0][a7], 1);
  ASSERT_EQ(files[0][a8], 1);
  ASSERT_EQ(files[9][j1], 1);
  ASSERT_EQ(files[9][j2], 1);
  ASSERT_EQ(files[9][j3], 1);
  ASSERT_EQ(files[9][j4], 1);
  ASSERT_EQ(files[9][j5], 1);
  ASSERT_EQ(files[9][j6], 1);
  ASSERT_EQ(files[9][j7], 1);
  ASSERT_EQ(files[9][j8], 1);
}

TEST_F(BitboardTest, RanksTest) {
  ASSERT_EQ(ranks[0][a1], 1);
  ASSERT_EQ(ranks[0][b1], 1);
  ASSERT_EQ(ranks[0][c1], 1);
  ASSERT_EQ(ranks[0][d1], 1);
  ASSERT_EQ(ranks[0][e1], 1);
  ASSERT_EQ(ranks[0][f1], 1);
  ASSERT_EQ(ranks[0][g1], 1);
  ASSERT_EQ(ranks[0][h1], 1);
  ASSERT_EQ(ranks[0][i1], 1);
  ASSERT_EQ(ranks[0][j1], 1);
  ASSERT_EQ(ranks[7][a8], 1);
  ASSERT_EQ(ranks[7][b8], 1);
  ASSERT_EQ(ranks[7][c8], 1);
  ASSERT_EQ(ranks[7][d8], 1);
  ASSERT_EQ(ranks[7][e8], 1);
  ASSERT_EQ(ranks[7][f8], 1);
  ASSERT_EQ(ranks[7][g8], 1);
  ASSERT_EQ(ranks[7][h8], 1);
  ASSERT_EQ(ranks[7][i8], 1);
  ASSERT_EQ(ranks[7][j8], 1);
}

} // namespace khet
