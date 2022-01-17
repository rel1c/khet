#include <gtest/gtest.h>

#include "piece.h"

class PieceTest : public::testing::Test {};

using PieceDeathTest = PieceTest;

TEST_F(PieceTest, ColorOfPieceTest) {
  ASSERT_EQ(SILVER, colorOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(SILVER, colorOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(SILVER, colorOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(SILVER, colorOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(RED, colorOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(RED, colorOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(RED, colorOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(RED, colorOf(RED_WEST_SPHINX));
}

TEST_F(PieceTest, DirectionNegationTest) {
  ASSERT_EQ(NORTH, ~SOUTH);
  ASSERT_EQ(EAST, ~WEST);
  ASSERT_EQ(SOUTH, ~NORTH);
  ASSERT_EQ(WEST, ~EAST);
}

TEST_F(PieceTest, DirectionOfPieceTest) {
  ASSERT_EQ(NORTH, directionOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(NORTH, directionOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(EAST, directionOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(EAST, directionOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(SOUTH, directionOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(SOUTH, directionOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(WEST, directionOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(WEST, directionOf(RED_WEST_SPHINX));
}

TEST_F(PieceTest, ReflectTest) {
  ASSERT_EQ(NORTH, reflect(SILVER_NORTH_EYE_OF_HORUS, WEST));
  ASSERT_EQ(NORTH, reflect(SILVER_NORTH_PYRAMID, WEST));
  ASSERT_EQ(NORTH, reflect(SILVER_NORTH_SCARAB, WEST));
  ASSERT_EQ(EAST, reflect(SILVER_NORTH_EYE_OF_HORUS, SOUTH));
  ASSERT_EQ(EAST, reflect(SILVER_NORTH_PYRAMID, SOUTH));
  ASSERT_EQ(EAST, reflect(SILVER_NORTH_SCARAB, SOUTH));
    //TODO fill this in... repeat for scarab/eyes N=S, W=E
}

TEST_F(PieceTest, MakePieceTest) {
  //TODO NO_PIECE,
  ASSERT_EQ(SILVER_NORTH_ANUBIS, make(SILVER, ANUBIS, NORTH));
  ASSERT_EQ(SILVER_EAST_ANUBIS, make(SILVER, ANUBIS, EAST));
  ASSERT_EQ(SILVER_SOUTH_ANUBIS, make(SILVER, ANUBIS, SOUTH));
  ASSERT_EQ(SILVER_WEST_ANUBIS, make(SILVER, ANUBIS, WEST));
  ASSERT_EQ(SILVER_NORTH_EYE_OF_HORUS, make(SILVER, EYE_OF_HORUS, NORTH));
  ASSERT_EQ(SILVER_EAST_EYE_OF_HORUS, make(SILVER, EYE_OF_HORUS, EAST));
  ASSERT_EQ(SILVER_SOUTH_EYE_OF_HORUS, make(SILVER, EYE_OF_HORUS, SOUTH));
  ASSERT_EQ(SILVER_WEST_EYE_OF_HORUS, make(SILVER, EYE_OF_HORUS, WEST));
  ASSERT_EQ(SILVER_NORTH_PHARAOH, make(SILVER, PHARAOH, NORTH));
  ASSERT_EQ(SILVER_EAST_PHARAOH, make(SILVER, PHARAOH, EAST));
  ASSERT_EQ(SILVER_SOUTH_PHARAOH, make(SILVER, PHARAOH, SOUTH));
  ASSERT_EQ(SILVER_WEST_PHARAOH, make(SILVER, PHARAOH, WEST));
  ASSERT_EQ(SILVER_NORTH_PYRAMID, make(SILVER, PYRAMID, NORTH));
  ASSERT_EQ(SILVER_EAST_PYRAMID, make(SILVER, PYRAMID, EAST));
  ASSERT_EQ(SILVER_SOUTH_PYRAMID, make(SILVER, PYRAMID, SOUTH));
  ASSERT_EQ(SILVER_WEST_PYRAMID, make(SILVER, PYRAMID, WEST));
  ASSERT_EQ(SILVER_NORTH_SCARAB, make(SILVER, SCARAB, NORTH));
  ASSERT_EQ(SILVER_EAST_SCARAB, make(SILVER, SCARAB, EAST));
  ASSERT_EQ(SILVER_SOUTH_SCARAB, make(SILVER, SCARAB, SOUTH));
  ASSERT_EQ(SILVER_WEST_SCARAB, make(SILVER, SCARAB, WEST));
  ASSERT_EQ(SILVER_NORTH_SPHINX, make(SILVER, SPHINX, NORTH));
  ASSERT_EQ(SILVER_EAST_SPHINX, make(SILVER, SPHINX, EAST));
  ASSERT_EQ(SILVER_SOUTH_SPHINX, make(SILVER, SPHINX, SOUTH));
  ASSERT_EQ(SILVER_WEST_SPHINX, make(SILVER, SPHINX, WEST));
  ASSERT_EQ(RED_NORTH_ANUBIS, make(RED, ANUBIS, NORTH));
  ASSERT_EQ(RED_EAST_ANUBIS, make(RED, ANUBIS, EAST));
  ASSERT_EQ(RED_SOUTH_ANUBIS, make(RED, ANUBIS, SOUTH));
  ASSERT_EQ(RED_WEST_ANUBIS, make(RED, ANUBIS, WEST));
  ASSERT_EQ(RED_NORTH_EYE_OF_HORUS, make(RED, EYE_OF_HORUS, NORTH));
  ASSERT_EQ(RED_EAST_EYE_OF_HORUS, make(RED, EYE_OF_HORUS, EAST));
  ASSERT_EQ(RED_SOUTH_EYE_OF_HORUS, make(RED, EYE_OF_HORUS, SOUTH));
  ASSERT_EQ(RED_WEST_EYE_OF_HORUS, make(RED, EYE_OF_HORUS, WEST));
  ASSERT_EQ(RED_NORTH_PHARAOH, make(RED, PHARAOH, NORTH));
  ASSERT_EQ(RED_EAST_PHARAOH, make(RED, PHARAOH, EAST));
  ASSERT_EQ(RED_SOUTH_PHARAOH, make(RED, PHARAOH, SOUTH));
  ASSERT_EQ(RED_WEST_PHARAOH, make(RED, PHARAOH, WEST));
  ASSERT_EQ(RED_NORTH_PYRAMID, make(RED, PYRAMID, NORTH));
  ASSERT_EQ(RED_EAST_PYRAMID, make(RED, PYRAMID, EAST));
  ASSERT_EQ(RED_SOUTH_PYRAMID, make(RED, PYRAMID, SOUTH));
  ASSERT_EQ(RED_WEST_PYRAMID, make(RED, PYRAMID, WEST));
  ASSERT_EQ(RED_NORTH_SCARAB, make(RED, SCARAB, NORTH));
  ASSERT_EQ(RED_EAST_SCARAB, make(RED, SCARAB, EAST));
  ASSERT_EQ(RED_SOUTH_SCARAB, make(RED, SCARAB, SOUTH));
  ASSERT_EQ(RED_WEST_SCARAB, make(RED, SCARAB, WEST));
  ASSERT_EQ(RED_NORTH_SPHINX, make(RED, SPHINX, NORTH));
  ASSERT_EQ(RED_EAST_SPHINX, make(RED, SPHINX, EAST));
  ASSERT_EQ(RED_SOUTH_SPHINX, make(RED, SPHINX, SOUTH));
  ASSERT_EQ(RED_WEST_SPHINX, make(RED, SPHINX, WEST));
}

TEST_F(PieceTest, TypeOfPieceTest) {
  ASSERT_EQ(ANUBIS, typeOf(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(ANUBIS, typeOf(RED_NORTH_ANUBIS));
  ASSERT_EQ(EYE_OF_HORUS, typeOf(SILVER_EAST_EYE_OF_HORUS));
  ASSERT_EQ(EYE_OF_HORUS, typeOf(RED_EAST_EYE_OF_HORUS));
  ASSERT_EQ(PYRAMID, typeOf(SILVER_SOUTH_PYRAMID));
  ASSERT_EQ(PYRAMID, typeOf(RED_SOUTH_PYRAMID));
  ASSERT_EQ(SCARAB, typeOf(SILVER_WEST_SCARAB));
  ASSERT_EQ(SPHINX, typeOf(RED_WEST_SPHINX));
}

TEST_F(PieceTest, RotatePosTest) {
  ASSERT_EQ(SILVER_EAST_ANUBIS, rotatePos(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(SILVER_SOUTH_ANUBIS, rotatePos(SILVER_EAST_ANUBIS));
  ASSERT_EQ(SILVER_WEST_ANUBIS, rotatePos(SILVER_SOUTH_ANUBIS));
  ASSERT_EQ(SILVER_NORTH_ANUBIS, rotatePos(SILVER_WEST_ANUBIS));
  ASSERT_EQ(RED_EAST_ANUBIS, rotatePos(RED_NORTH_ANUBIS));
  ASSERT_EQ(RED_SOUTH_ANUBIS, rotatePos(RED_EAST_ANUBIS));
  ASSERT_EQ(RED_WEST_ANUBIS, rotatePos(RED_SOUTH_ANUBIS));
  ASSERT_EQ(RED_NORTH_ANUBIS, rotatePos(RED_WEST_ANUBIS));
}

TEST_F(PieceTest, RotateNegTest) {
  ASSERT_EQ(SILVER_WEST_ANUBIS, rotateNeg(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(SILVER_NORTH_ANUBIS, rotateNeg(SILVER_EAST_ANUBIS));
  ASSERT_EQ(SILVER_EAST_ANUBIS, rotateNeg(SILVER_SOUTH_ANUBIS));
  ASSERT_EQ(SILVER_SOUTH_ANUBIS, rotateNeg(SILVER_WEST_ANUBIS));
  ASSERT_EQ(RED_WEST_ANUBIS, rotateNeg(RED_NORTH_ANUBIS));
  ASSERT_EQ(RED_NORTH_ANUBIS, rotateNeg(RED_EAST_ANUBIS));
  ASSERT_EQ(RED_EAST_ANUBIS, rotateNeg(RED_SOUTH_ANUBIS));
  ASSERT_EQ(RED_SOUTH_ANUBIS, rotateNeg(RED_WEST_ANUBIS));
}

TEST_F(PieceTest, FlipTest) {
  ASSERT_EQ(SILVER_WEST_ANUBIS, flip(SILVER_NORTH_ANUBIS));
  ASSERT_EQ(SILVER_SOUTH_ANUBIS, flip(SILVER_EAST_ANUBIS));
  ASSERT_EQ(SILVER_EAST_ANUBIS, flip(SILVER_SOUTH_ANUBIS));
  ASSERT_EQ(SILVER_NORTH_ANUBIS, flip(SILVER_WEST_ANUBIS));
  ASSERT_EQ(RED_WEST_ANUBIS, flip(RED_NORTH_ANUBIS));
  ASSERT_EQ(RED_SOUTH_ANUBIS, flip(RED_EAST_ANUBIS));
  ASSERT_EQ(RED_EAST_ANUBIS, flip(RED_SOUTH_ANUBIS));
  ASSERT_EQ(RED_NORTH_ANUBIS, flip(RED_WEST_ANUBIS));
}

TEST_F(PieceDeathTest, ColorOfPieceDeathTest) {
  ASSERT_DEATH(colorOf(NO_PIECE), "");
}

TEST_F(PieceDeathTest, DirectionOfPieceDeathTest) {
  ASSERT_DEATH(directionOf(NO_PIECE), "");
}

TEST_F(PieceDeathTest, ReflectDeathTest) {
  ASSERT_DEATH(reflect(NO_PIECE, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_NORTH_ANUBIS, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_NORTH_PHARAOH, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_NORTH_SPHINX, NORTH), "");
  ASSERT_DEATH(reflect(RED_NORTH_ANUBIS, NORTH), "");
  ASSERT_DEATH(reflect(RED_NORTH_PHARAOH, NORTH), "");
  ASSERT_DEATH(reflect(RED_NORTH_SPHINX, NORTH), "");
}
