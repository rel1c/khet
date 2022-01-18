#include <gtest/gtest.h>

#include "test_util.h"
#include "piece.h"

class PieceTest : public::testing::Test {};
class PieceTestParam : public ::testing::TestWithParam<std::tuple<Piece, Color, PieceType, Direction>> {};

using PieceDeathTest = PieceTest;
using PieceDeathTestParam = PieceTestParam;

TEST_P(PieceTestParam, ColorOfTest) {
  Piece p = std::get<0>(GetParam());
  Color c = std::get<1>(GetParam());
  ASSERT_EQ(c, colorOf(p));
}

TEST_F(PieceTest, DirectionNegationTest) {
  ASSERT_EQ(NORTH, ~SOUTH);
  ASSERT_EQ(EAST, ~WEST);
  ASSERT_EQ(SOUTH, ~NORTH);
  ASSERT_EQ(WEST, ~EAST);
}

TEST_P(PieceTestParam, DirectionOfTest) {
  Piece p = std::get<0>(GetParam());
  Direction d = std::get<3>(GetParam());
  ASSERT_EQ(d, directionOf(p));
}

TEST_P(PieceTestParam, ReflectTest) {
  Piece p = std::get<0>(GetParam());
  Direction d = std::get<3>(GetParam());
  PieceType pt = std::get<2>(GetParam());
  if (pt != EYE_OF_HORUS || pt != PYRAMID || pt != SCARAB)
    return;
  if (d == NORTH || d == SOUTH) {
    ASSERT_EQ(WEST, reflect(p, NORTH));
    ASSERT_EQ(SOUTH, reflect(p, EAST));
    ASSERT_EQ(EAST, reflect(p, SOUTH));
    ASSERT_EQ(NORTH, reflect(p, WEST));
  }
  else {
    ASSERT_EQ(EAST, reflect(p, NORTH));
    ASSERT_EQ(SOUTH, reflect(p, WEST));
    ASSERT_EQ(WEST, reflect(p, SOUTH));
    ASSERT_EQ(NORTH, reflect(p, EAST));
  }
}

TEST_F(PieceTest, DirectionFromCharTest) {
  ASSERT_EQ(NORTH, directionFromChar('n'));
  ASSERT_EQ(EAST, directionFromChar('e'));
  ASSERT_EQ(SOUTH, directionFromChar('s'));
  ASSERT_EQ(WEST, directionFromChar('w'));
}

TEST_F(PieceTest, DirectionToCharTest) {
  ASSERT_EQ('n', toChar(NORTH));
  ASSERT_EQ('e', toChar(EAST));
  ASSERT_EQ('s', toChar(SOUTH));
  ASSERT_EQ('w', toChar(WEST));
}

TEST_P(PieceTestParam, TypeOfTest) {
  Piece p = std::get<0>(GetParam());
  PieceType pt = std::get<2>(GetParam());
  ASSERT_EQ(pt, typeOf(p));
}

TEST_F(PieceTest, PieceTypeToCharTest) {
  ASSERT_EQ(' ', toChar(NO_PIECE_TYPE));
  ASSERT_EQ('a', toChar(ANUBIS));
  ASSERT_EQ('x', toChar(SPHINX));
  ASSERT_EQ('r', toChar(PHARAOH));
  ASSERT_EQ('p', toChar(PYRAMID));
  ASSERT_EQ('s', toChar(SCARAB));
  ASSERT_EQ('e', toChar(EYE_OF_HORUS));
  ASSERT_EQ(' ', toChar(ALL_PIECES));
}

TEST_F(PieceTest, PieceTypeFromCharTest) {
  ASSERT_EQ(ANUBIS, pieceTypeFromChar('a'));
  ASSERT_EQ(SPHINX, pieceTypeFromChar('x'));
  ASSERT_EQ(PHARAOH, pieceTypeFromChar('r'));
  ASSERT_EQ(PYRAMID, pieceTypeFromChar('p'));
  ASSERT_EQ(SCARAB, pieceTypeFromChar('s'));
  ASSERT_EQ(EYE_OF_HORUS, pieceTypeFromChar('e'));
  ASSERT_EQ(ANUBIS, pieceTypeFromChar('A'));
  ASSERT_EQ(SPHINX, pieceTypeFromChar('X'));
  ASSERT_EQ(PHARAOH, pieceTypeFromChar('R'));
  ASSERT_EQ(PYRAMID, pieceTypeFromChar('P'));
  ASSERT_EQ(SCARAB, pieceTypeFromChar('S'));
  ASSERT_EQ(EYE_OF_HORUS, pieceTypeFromChar('E'));
}

TEST_P(PieceTestParam, MakeTest) {
  Piece p = std::get<0>(GetParam());
  Color c = std::get<1>(GetParam());
  PieceType pt = std::get<2>(GetParam());
  Direction d = std::get<3>(GetParam());
  ASSERT_EQ(p, make(c, pt, d));
}

TEST_P(PieceTestParam, RotatePosTest) {
  Piece p1 = std::get<0>(GetParam());
  Color c1 = std::get<1>(GetParam());
  PieceType pt1 = std::get<2>(GetParam());
  Direction d1 = std::get<3>(GetParam());
  Piece p2 = rotatePos(p1);
  Color c2 = colorOf(p2);
  PieceType pt2 = typeOf(p2);
  Direction d2 = directionOf(p2);
  ASSERT_NE(p1, p2);
  EXPECT_EQ(c1, c2);
  ASSERT_NE(d1, d2);
  EXPECT_EQ(pt1, pt2);
  if (d1 == NORTH)
    EXPECT_EQ(d2, EAST);
  else if (d1 == EAST)
    EXPECT_EQ(d2, SOUTH);
  else if (d1 == SOUTH)
    EXPECT_EQ(d2, WEST);
  else
    EXPECT_EQ(d2, NORTH);
}

TEST_P(PieceTestParam, RotateNegTest) {
  Piece p1 = std::get<0>(GetParam());
  Color c1 = std::get<1>(GetParam());
  PieceType pt1 = std::get<2>(GetParam());
  Direction d1 = std::get<3>(GetParam());
  Piece p2 = rotateNeg(p1);
  Color c2 = colorOf(p2);
  PieceType pt2 = typeOf(p2);
  Direction d2 = directionOf(p2);
  ASSERT_NE(p1, p2);
  EXPECT_EQ(c1, c2);
  ASSERT_NE(d1, d2);
  EXPECT_EQ(pt1, pt2);
  if (d1 == NORTH)
    EXPECT_EQ(d2, WEST);
  else if (d1 == EAST)
    EXPECT_EQ(d2, NORTH);
  else if (d1 == SOUTH)
    EXPECT_EQ(d2, EAST);
  else
    EXPECT_EQ(d2, SOUTH);
}

TEST_P(PieceTestParam, FlipTest) {
  Piece p1 = std::get<0>(GetParam());
  Color c1 = std::get<1>(GetParam());
  PieceType pt1 = std::get<2>(GetParam());
  Direction d1 = std::get<3>(GetParam());
  Piece p2 = flip(p1);
  Color c2 = colorOf(p2);
  PieceType pt2 = typeOf(p2);
  Direction d2 = directionOf(p2);
  ASSERT_NE(p1, p2);
  EXPECT_EQ(c1, c2);
  ASSERT_NE(d1, d2);
  EXPECT_EQ(pt1, pt2);
  if (d1 == NORTH)
    EXPECT_EQ(d2, WEST);
  else if (d1 == EAST)
    EXPECT_EQ(d2, SOUTH);
  else if (d1 == SOUTH)
    EXPECT_EQ(d2, EAST);
  else
    EXPECT_EQ(d2, NORTH);
}

// DEATH TESTS //

TEST_F(PieceDeathTest, ColorOfDeathTest) {
  ASSERT_DEATH(colorOf(NO_PIECE), "");
}

TEST_F(PieceDeathTest, DirectionOfeDeathTest) {
  ASSERT_DEATH(directionOf(NO_PIECE), "");
}

TEST_F(PieceDeathTest, ReflectDeathTest) {
  ASSERT_DEATH(reflect(NO_PIECE, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_ANUBIS_NORTH, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_PHARAOH_NORTH, NORTH), "");
  ASSERT_DEATH(reflect(SILVER_SPHINX_NORTH, NORTH), "");
  ASSERT_DEATH(reflect(RED_ANUBIS_NORTH, NORTH), "");
  ASSERT_DEATH(reflect(RED_PHARAOH_NORTH, NORTH), "");
  ASSERT_DEATH(reflect(RED_SPHINX_NORTH, NORTH), "");
}

TEST_F(PieceTest, DirectionFromCharDeathTest) {
  ASSERT_DEATH(directionFromChar('g'), "");
  ASSERT_DEATH(directionFromChar('Q'), "");
  ASSERT_DEATH(directionFromChar(' '), "");
  ASSERT_DEATH(directionFromChar('?'), "");
}

TEST_F(PieceTest, PieceTypeFromCharDeathTest) {
  ASSERT_DEATH(pieceTypeFromChar('g'), "");
  ASSERT_DEATH(directionFromChar('Q'), "");
  ASSERT_DEATH(pieceTypeFromChar(' '), "");
  ASSERT_DEATH(pieceTypeFromChar('?'), "");
}

INSTANTIATE_TEST_SUITE_P(
  PieceTests,
  PieceTestParam,
  ::testing::Values(
    std::make_tuple(SILVER_ANUBIS_NORTH, SILVER, ANUBIS, NORTH),
    std::make_tuple(SILVER_ANUBIS_EAST, SILVER, ANUBIS, EAST),
    std::make_tuple(SILVER_ANUBIS_SOUTH, SILVER, ANUBIS, SOUTH),
    std::make_tuple(SILVER_ANUBIS_WEST, SILVER, ANUBIS, WEST),
    std::make_tuple(SILVER_EYE_OF_HORUS_NORTH, SILVER, EYE_OF_HORUS, NORTH),
    std::make_tuple(SILVER_EYE_OF_HORUS_EAST, SILVER, EYE_OF_HORUS, EAST),
    std::make_tuple(SILVER_EYE_OF_HORUS_SOUTH, SILVER, EYE_OF_HORUS, SOUTH),
    std::make_tuple(SILVER_EYE_OF_HORUS_WEST, SILVER, EYE_OF_HORUS, WEST),
    std::make_tuple(SILVER_PHARAOH_NORTH, SILVER, PHARAOH, NORTH),
    std::make_tuple(SILVER_PHARAOH_EAST, SILVER, PHARAOH, EAST),
    std::make_tuple(SILVER_PHARAOH_SOUTH, SILVER, PHARAOH, SOUTH),
    std::make_tuple(SILVER_PHARAOH_WEST, SILVER, PHARAOH, WEST),
    std::make_tuple(SILVER_PYRAMID_NORTH, SILVER, PYRAMID, NORTH),
    std::make_tuple(SILVER_PYRAMID_EAST, SILVER, PYRAMID, EAST),
    std::make_tuple(SILVER_PYRAMID_SOUTH, SILVER, PYRAMID, SOUTH),
    std::make_tuple(SILVER_PYRAMID_WEST, SILVER, PYRAMID, WEST),
    std::make_tuple(SILVER_SCARAB_NORTH, SILVER, SCARAB, NORTH),
    std::make_tuple(SILVER_SCARAB_EAST, SILVER, SCARAB, EAST),
    std::make_tuple(SILVER_SCARAB_SOUTH, SILVER, SCARAB, SOUTH),
    std::make_tuple(SILVER_SCARAB_WEST, SILVER, SCARAB, WEST),
    std::make_tuple(SILVER_SPHINX_NORTH, SILVER, SPHINX, NORTH),
    std::make_tuple(SILVER_SPHINX_EAST, SILVER, SPHINX, EAST),
    std::make_tuple(SILVER_SPHINX_SOUTH, SILVER, SPHINX, SOUTH),
    std::make_tuple(SILVER_SPHINX_WEST, SILVER, SPHINX, WEST),
    std::make_tuple(RED_ANUBIS_NORTH, RED, ANUBIS, NORTH),
    std::make_tuple(RED_ANUBIS_EAST, RED, ANUBIS, EAST),
    std::make_tuple(RED_ANUBIS_SOUTH, RED, ANUBIS, SOUTH),
    std::make_tuple(RED_ANUBIS_WEST, RED, ANUBIS, WEST),
    std::make_tuple(RED_EYE_OF_HORUS_NORTH, RED, EYE_OF_HORUS, NORTH),
    std::make_tuple(RED_EYE_OF_HORUS_EAST, RED, EYE_OF_HORUS, EAST),
    std::make_tuple(RED_EYE_OF_HORUS_SOUTH, RED, EYE_OF_HORUS, SOUTH),
    std::make_tuple(RED_EYE_OF_HORUS_WEST, RED, EYE_OF_HORUS, WEST),
    std::make_tuple(RED_PHARAOH_NORTH, RED, PHARAOH, NORTH),
    std::make_tuple(RED_PHARAOH_EAST, RED, PHARAOH, EAST),
    std::make_tuple(RED_PHARAOH_SOUTH, RED, PHARAOH, SOUTH),
    std::make_tuple(RED_PHARAOH_WEST, RED, PHARAOH, WEST),
    std::make_tuple(RED_PYRAMID_NORTH, RED, PYRAMID, NORTH),
    std::make_tuple(RED_PYRAMID_EAST, RED, PYRAMID, EAST),
    std::make_tuple(RED_PYRAMID_SOUTH, RED, PYRAMID, SOUTH),
    std::make_tuple(RED_PYRAMID_WEST, RED, PYRAMID, WEST),
    std::make_tuple(RED_SCARAB_NORTH, RED, SCARAB, NORTH),
    std::make_tuple(RED_SCARAB_EAST, RED, SCARAB, EAST),
    std::make_tuple(RED_SCARAB_SOUTH, RED, SCARAB, SOUTH),
    std::make_tuple(RED_SCARAB_WEST, RED, SCARAB, WEST),
    std::make_tuple(RED_SPHINX_NORTH, RED, SPHINX, NORTH),
    std::make_tuple(RED_SPHINX_EAST, RED, SPHINX, EAST),
    std::make_tuple(RED_SPHINX_SOUTH, RED, SPHINX, SOUTH),
    std::make_tuple(RED_SPHINX_WEST, RED, SPHINX, WEST)
  )
);
