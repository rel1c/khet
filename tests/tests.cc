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

TEST_F(TypesTest, ColorOfPieceTest) {
  EXPECT_EQ(SILVER, colorOf(SILVER_NORTH_ANUBIS));
  EXPECT_EQ(SILVER, colorOf(SILVER_EAST_EYE_OF_HORUS));
  EXPECT_EQ(SILVER, colorOf(SILVER_SOUTH_PYRAMID));
  EXPECT_EQ(SILVER, colorOf(SILVER_WEST_SCARAB));
  EXPECT_EQ(RED, colorOf(RED_NORTH_ANUBIS));
  EXPECT_EQ(RED, colorOf(RED_EAST_EYE_OF_HORUS));
  EXPECT_EQ(RED, colorOf(RED_SOUTH_PYRAMID));
  EXPECT_EQ(RED, colorOf(RED_WEST_SCARAB));
}

TEST_F(TypesTest, DirectionOfPieceTest) {
  EXPECT_EQ(NORTH, directionOf(SILVER_NORTH_ANUBIS));
  EXPECT_EQ(NORTH, directionOf(RED_NORTH_ANUBIS));
  EXPECT_EQ(EAST, directionOf(SILVER_EAST_EYE_OF_HORUS));
  EXPECT_EQ(EAST, directionOf(RED_EAST_EYE_OF_HORUS));
  EXPECT_EQ(SOUTH, directionOf(SILVER_SOUTH_PYRAMID));
  EXPECT_EQ(SOUTH, directionOf(RED_SOUTH_PYRAMID));
  EXPECT_EQ(WEST, directionOf(SILVER_WEST_SCARAB));
  EXPECT_EQ(WEST, directionOf(RED_WEST_SCARAB));
}

TEST_F(TypesTest, TypeOfPieceTest) {
  EXPECT_EQ(ANUBIS, typeOf(SILVER_NORTH_ANUBIS));
  EXPECT_EQ(ANUBIS, typeOf(RED_NORTH_ANUBIS));
  EXPECT_EQ(EYE_OF_HORUS, typeOf(SILVER_EAST_EYE_OF_HORUS));
  EXPECT_EQ(EYE_OF_HORUS, typeOf(RED_EAST_EYE_OF_HORUS));
  EXPECT_EQ(PYRAMID, typeOf(SILVER_SOUTH_PYRAMID));
  EXPECT_EQ(PYRAMID, typeOf(RED_SOUTH_PYRAMID));
  EXPECT_EQ(SCARAB, typeOf(SILVER_WEST_SCARAB));
  EXPECT_EQ(SCARAB, typeOf(RED_WEST_SCARAB));
}
