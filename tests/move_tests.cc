#include <gtest/gtest.h>

#include "test_util.h"
#include "move.h"

class MoveTest : public::testing::Test {
protected:
  Move m;
};

TEST_F(MoveTest, BasicMakeMoveTest) {
  m = makeMove(SQ_C1, SQ_B2);
  EXPECT_EQ(m, 0b0000010000001011);
  m = makeMove(SQ_A1, SQ_A2, true);
  EXPECT_EQ(m, 0b0000000010001010);
  m = makeMove(SQ_B2, POSITIVE);
  EXPECT_EQ(m, 0b0001011100000000);
  m = makeMove(SQ_C2, NEGATIVE);
  EXPECT_EQ(m, 0b0001100100000001);
}

TEST_F(MoveTest, GetFromMoveTest) {
  m = makeMove(SQ_C1, SQ_B2);
  EXPECT_EQ(SQ_C1, getFrom(m));
  m = makeMove(SQ_B2, POSITIVE);
  EXPECT_EQ(SQ_B2, getFrom(m));
}

TEST_F(MoveTest, GetToMoveTest) {
  m = makeMove(SQ_C1, SQ_B2);
  EXPECT_EQ(SQ_B2, getTo(m));
  m = makeMove(SQ_B2, SQ_C1, true);
  EXPECT_EQ(SQ_C1, getTo(m));
}

TEST_F(MoveTest, IsRotateMoveTest) {
  m = makeMove(SQ_J8, NEGATIVE);
  EXPECT_TRUE(isRotate(m));
  m = makeMove(SQ_J8, POSITIVE);
  EXPECT_TRUE(isRotate(m));
  m = makeMove(SQ_B2, SQ_C1, true);
  EXPECT_FALSE(isRotate(m));
  m = makeMove(SQ_B2, SQ_C1);
  EXPECT_FALSE(isRotate(m));
}

TEST_F(MoveTest, IsSwapMoveTest) {
  m = makeMove(SQ_J8, NEGATIVE);
  EXPECT_FALSE(isSwap(m));
  m = makeMove(SQ_J8, POSITIVE);
  EXPECT_FALSE(isSwap(m));
  m = makeMove(SQ_B2, SQ_C1, true);
  EXPECT_TRUE(isSwap(m));
  m = makeMove(SQ_B2, SQ_C1);
  EXPECT_FALSE(isSwap(m));
}

TEST_F(MoveTest, GetRotationMoveTest) {
  m = makeMove(SQ_J8, NEGATIVE);
  EXPECT_EQ(NEGATIVE, getRotation(m));
  m = makeMove(SQ_J8, POSITIVE);
  EXPECT_EQ(POSITIVE, getRotation(m));
}
