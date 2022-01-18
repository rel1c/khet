#include <gtest/gtest.h>

#include "test_util.h"
#include "board.h"

class BoardTest : public::testing::Test {};
class BoardTestParam : public ::testing::TestWithParam<std::tuple<std::string, std::array<Piece, NUM_SQUARES>>> {};

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
  ASSERT_EQ(RANK_8, rankOf(SQ_J8));
  ASSERT_EQ(RANK_1, rankOf(SQ_J1));
  ASSERT_EQ(RANK_2, rankOf(SQ_I2));
}

TEST_P(BoardTestParam, SetPknTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  std::array<Piece, NUM_SQUARES> pieces = std::get<1>(GetParam());
  b.setPkn(pkn);
  EXPECT_EQ(pkn, b.toPkn());
}

TEST_P(BoardTestParam, ToPknTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  std::array<Piece, NUM_SQUARES> pieces = std::get<1>(GetParam());
  //b.setPkn(pkn);
  for (int i = 0; i < NUM_SQUARES; i++) {
    Piece p = pieces[i];
    if (p) {
      Color c = colorOf(p);
      PieceType pt = typeOf(p);
      Direction d = directionOf(p);
      Square s = static_cast<Square>(i);
      b.addPiece(s, c, pt, d);
    }
  }
  EXPECT_EQ(pkn, b.toPkn());
}

INSTANTIATE_TEST_SUITE_P(
  BoardTests,
  BoardTestParam,
  ::testing::Values(
    std::make_tuple(
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ NO_PIECE,
        /* C1 */ SILVER_PYRAMID_WEST,
        /* D1 */ SILVER_ANUBIS_NORTH,
        /* E1 */ SILVER_PHARAOH_NORTH,
        /* F1 */ SILVER_ANUBIS_NORTH,
        /* G1 */ NO_PIECE,
        /* H1 */ NO_PIECE,
        /* I1 */ NO_PIECE,
        /* J1 */ SILVER_SPHINX_NORTH,
        /* A2 */ NO_PIECE,
        /* B2 */ NO_PIECE,
        /* C2 */ NO_PIECE,
        /* D2 */ NO_PIECE,
        /* E2 */ NO_PIECE,
        /* F2 */ NO_PIECE,
        /* G2 */ NO_PIECE,
        /* H2 */ SILVER_PYRAMID_NORTH,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ NO_PIECE,
        /* E3 */ NO_PIECE,
        /* F3 */ NO_PIECE,
        /* G3 */ RED_PYRAMID_EAST,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ NO_PIECE,
        /* A4 */ RED_PYRAMID_EAST,
        /* B4 */ NO_PIECE,
        /* C4 */ SILVER_PYRAMID_WEST,
        /* D4 */ NO_PIECE,
        /* E4 */ SILVER_SCARAB_WEST,
        /* F4 */ SILVER_SCARAB_SOUTH,
        /* G4 */ NO_PIECE,
        /* H4 */ RED_PYRAMID_NORTH,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ NO_PIECE,
        /* C5 */ SILVER_PYRAMID_SOUTH,
        /* D5 */ NO_PIECE,
        /* E5 */ RED_SCARAB_NORTH,
        /* F5 */ RED_SCARAB_EAST,
        /* G5 */ NO_PIECE,
        /* H5 */ RED_PYRAMID_EAST,
        /* I5 */ NO_PIECE,
        /* J5 */ SILVER_PYRAMID_WEST,
        /* A6 */ NO_PIECE,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ SILVER_PYRAMID_WEST,
        /* E6 */ NO_PIECE,
        /* F6 */ NO_PIECE,
        /* G6 */ NO_PIECE,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ RED_PYRAMID_SOUTH,
        /* D7 */ NO_PIECE,
        /* E7 */ NO_PIECE,
        /* F7 */ NO_PIECE,
        /* G7 */ NO_PIECE,
        /* H7 */ NO_PIECE,
        /* I7 */ NO_PIECE,
        /* J7 */ NO_PIECE,
        /* A8 */ RED_SPHINX_SOUTH,
        /* B8 */ NO_PIECE,
        /* C8 */ NO_PIECE,
        /* D8 */ NO_PIECE,
        /* E8 */ RED_ANUBIS_SOUTH,
        /* F8 */ RED_PHARAOH_SOUTH,
        /* G8 */ RED_ANUBIS_SOUTH,
        /* H8 */ RED_PYRAMID_EAST,
        /* I8 */ NO_PIECE,
        /* J8 */ NO_PIECE
      }
    )
  )
);
