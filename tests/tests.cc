#include "bitboard.h"

#include <gtest/gtest.h>

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
  bb = initBitboard(std::vector<int> {A1, E5, J8});
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

} // namespace khet
