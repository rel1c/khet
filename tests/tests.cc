#include "types.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <iostream>
#include <streambuf>
#include <string>
#include <tuple>
#include <vector>

class CoutRedirect {
public:
  CoutRedirect() {
    old = std::cout.rdbuf(buffer.rdbuf());
  }

  std::string getString() {
    return buffer.str();
  }

  ~CoutRedirect() {
    std::cout.rdbuf(old);
  }
private:
    std::stringstream buffer;
    std::streambuf* old;
};

class TypesTest : public::testing::Test {};

using TypesDeathTest = TypesTest;

TEST_F(TypesTest, ColorOfPieceTest) {
  ASSERT_EQ(SILVER, colorOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(SILVER, colorOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(SILVER, colorOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(SILVER, colorOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(RED, colorOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(RED, colorOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(RED, colorOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(RED, colorOf(RED_WEST_SPHINX));
}

TEST_F(TypesTest, DirectionOfPieceTest) {
  ASSERT_EQ(NORTH, directionOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(NORTH, directionOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(EAST, directionOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(EAST, directionOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(SOUTH, directionOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(SOUTH, directionOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(WEST, directionOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(WEST, directionOf(RED_WEST_SPHINX));
}

TEST_F(TypesTest, TypeOfPieceTest) {
  ASSERT_EQ(ANUBIS, typeOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(ANUBIS, typeOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(EYE_OF_HORUS, typeOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(EYE_OF_HORUS, typeOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(PYRAMID, typeOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(PYRAMID, typeOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(SCARAB, typeOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(SPHINX, typeOf(RED_WEST_SPHINX));
}

TEST_F(TypesTest, RotatePosTest) {
  ASSERT_EQ(rotatePos(SILVER_NORTH_ANUBIS), SILVER_EAST_ANUBIS);
  ASSERT_EQ(rotatePos(SILVER_EAST_ANUBIS), SILVER_SOUTH_ANUBIS);
  ASSERT_EQ(rotatePos(SILVER_SOUTH_ANUBIS), SILVER_WEST_ANUBIS);
  ASSERT_EQ(rotatePos(SILVER_WEST_ANUBIS), SILVER_NORTH_ANUBIS);
  ASSERT_EQ(rotatePos(RED_NORTH_ANUBIS), RED_EAST_ANUBIS);
  ASSERT_EQ(rotatePos(RED_EAST_ANUBIS), RED_SOUTH_ANUBIS);
  ASSERT_EQ(rotatePos(RED_SOUTH_ANUBIS), RED_WEST_ANUBIS);
  ASSERT_EQ(rotatePos(RED_WEST_ANUBIS), RED_NORTH_ANUBIS);
}

TEST_F(TypesTest, RotateNegTest) {
  ASSERT_EQ(rotateNeg(SILVER_NORTH_ANUBIS), SILVER_WEST_ANUBIS);
  ASSERT_EQ(rotateNeg(SILVER_EAST_ANUBIS), SILVER_NORTH_ANUBIS);
  ASSERT_EQ(rotateNeg(SILVER_SOUTH_ANUBIS), SILVER_EAST_ANUBIS);
  ASSERT_EQ(rotateNeg(SILVER_WEST_ANUBIS), SILVER_SOUTH_ANUBIS);
  ASSERT_EQ(rotateNeg(RED_NORTH_ANUBIS), RED_WEST_ANUBIS);
  ASSERT_EQ(rotateNeg(RED_EAST_ANUBIS), RED_NORTH_ANUBIS);
  ASSERT_EQ(rotateNeg(RED_SOUTH_ANUBIS), RED_EAST_ANUBIS);
  ASSERT_EQ(rotateNeg(RED_WEST_ANUBIS), RED_SOUTH_ANUBIS);
}

TEST_F(TypesTest, FlipTest) {
  ASSERT_EQ(flip(SILVER_NORTH_ANUBIS), SILVER_WEST_ANUBIS);
  ASSERT_EQ(flip(SILVER_EAST_ANUBIS), SILVER_SOUTH_ANUBIS);
  ASSERT_EQ(flip(SILVER_SOUTH_ANUBIS), SILVER_EAST_ANUBIS);
  ASSERT_EQ(flip(SILVER_WEST_ANUBIS), SILVER_NORTH_ANUBIS);
  ASSERT_EQ(flip(RED_NORTH_ANUBIS), RED_WEST_ANUBIS);
  ASSERT_EQ(flip(RED_EAST_ANUBIS), RED_SOUTH_ANUBIS);
  ASSERT_EQ(flip(RED_SOUTH_ANUBIS), RED_EAST_ANUBIS);
  ASSERT_EQ(flip(RED_WEST_ANUBIS), RED_NORTH_ANUBIS);
}

TEST_F(TypesTest, FileOfTest) {
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

TEST_F(TypesTest, RankOfTest) {
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

TEST_F(TypesDeathTest, ColorOfPieceDeathTest) {
  ASSERT_DEATH(colorOf(NO_PIECE), "");
}

TEST_F(TypesDeathTest, DirectionOfPieceDeathTest) {
  ASSERT_DEATH(directionOf(NO_PIECE), "");
}
