#include <gtest/gtest.h>

#include "test_util.h"
#include "board.h"

class BoardTest : public::testing::Test {};

using BoardDeathTest = BoardTest;

TEST_F(BoardTest, FileOfTest) {
  ASSERT_EQ(FILE_A, fileOf(SQ_A1));
  ASSERT_EQ(FILE_B, fileOf(SQ_B2));
  ASSERT_EQ(FILE_C, fileOf(SQ_C3));
  ASSERT_EQ(FILE_D, fileOf(SQ_D4));
  ASSERT_EQ(FILE_E, fileOf(SQ_E5));
  ASSERT_EQ(FILE_F, fileOf(SQ_F6));
  ASSERT_EQ(FILE_G, fileOf(SQ_G7));
  ASSERT_EQ(FILE_H, fileOf(SQ_H8));
  ASSERT_EQ(FILE_J, fileOf(SQ_J1));
  ASSERT_EQ(FILE_I, fileOf(SQ_I2));
}

TEST_F(BoardTest, RankOfTest) {
  ASSERT_EQ(RANK_1, rankOf(SQ_A1));
  ASSERT_EQ(RANK_2, rankOf(SQ_B2));
  ASSERT_EQ(RANK_3, rankOf(SQ_C3));
  ASSERT_EQ(RANK_4, rankOf(SQ_D4));
  ASSERT_EQ(RANK_5, rankOf(SQ_E5));
  ASSERT_EQ(RANK_6, rankOf(SQ_F6));
  ASSERT_EQ(RANK_7, rankOf(SQ_G7));
  ASSERT_EQ(RANK_8, rankOf(SQ_H8));
  ASSERT_EQ(RANK_1, rankOf(SQ_J1));
  ASSERT_EQ(RANK_2, rankOf(SQ_I2));
}
