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

TEST_P(BoardTestParam, PknTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  std::array<Piece, NUM_SQUARES> pieces = std::get<1>(GetParam());
  b.setPkn(pkn);
  ASSERT_EQ(pkn, b.toPkn());
}

TEST_P(BoardTestParam, AddPieceTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  std::array<Piece, NUM_SQUARES> pieces = std::get<1>(GetParam());
  for (int i = 0; i < NUM_SQUARES; i++) {
    Piece p = pieces[i];
    if (p) {
      Square s = static_cast<Square>(i);
      b.addPiece(p, s);
      Color c = colorOf(p);
      PieceType pt = typeOf(p);
      Direction d = directionOf(p);
      EXPECT_TRUE(b.pieces(c)[s]);
      EXPECT_TRUE(b.pieces(pt)[s]);
      EXPECT_TRUE(b.pieces(d)[s]);
    }
  }
  EXPECT_EQ(pkn, b.toPkn());
}

TEST_P(BoardTestParam, RemovePieceTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  std::array<Piece, NUM_SQUARES> pieces = std::get<1>(GetParam());
  for (int i = 0; i < NUM_SQUARES; i++) {
    Piece p = pieces[i];
    if (p) {
      Square s = static_cast<Square>(i);
      b.removePiece(p, s);
      Color c = colorOf(p);
      PieceType pt = typeOf(p);
      Direction d = directionOf(p);
      EXPECT_FALSE(b.pieceOn(s));
      EXPECT_FALSE(b.pieces(c)[s]);
      EXPECT_FALSE(b.pieces(pt)[s]);
      EXPECT_FALSE(b.pieces(d)[s]);
    }
  }
}

TEST_F(BoardTest, MovePieceTest) {
  Board b;
  Piece p = make(SILVER, ANUBIS, NORTH);
  b.addPiece(p, SQ_A1);
  for (int i = 0; i < NUM_SQUARES - 1; i++) {
    Square here = static_cast<Square>(i);
    Square there = static_cast<Square>(i + 1);
    Color c = colorOf(p);
    PieceType pt = typeOf(p);
    Direction d = directionOf(p);
    EXPECT_TRUE(b.pieceOn(here));
    EXPECT_TRUE(b.pieces(c)[here]);
    EXPECT_TRUE(b.pieces(pt)[here]);
    EXPECT_TRUE(b.pieces(d)[here]);
    EXPECT_FALSE(b.pieceOn(there));
    EXPECT_FALSE(b.pieces(c)[there]);
    EXPECT_FALSE(b.pieces(pt)[there]);
    EXPECT_FALSE(b.pieces(d)[there]);
    b.movePiece(here, there);
  }
}

TEST_F(BoardTest, SwapPieceTest) {
  Board b;
  Piece p = make(SILVER, PYRAMID, NORTH);
  Piece q = make(RED, SCARAB, SOUTH);
  Square from = SQ_A1;
  Square to = SQ_B1;
  b.addPiece(p, from);
  b.addPiece(q, to);

  Color c1 = colorOf(p);
  PieceType pt1 = typeOf(p);
  Direction d1 = directionOf(p);
  Color c2 = colorOf(q);
  PieceType pt2 = typeOf(q);
  Direction d2 = directionOf(q);

  ASSERT_TRUE(b.pieceOn(from));
  ASSERT_TRUE(b.pieceOn(to));
  ASSERT_NE(b.pieceOn(from), b.pieceOn(to));
  ASSERT_NE(c1, c2);
  ASSERT_NE(pt1, pt2);
  ASSERT_NE(d1, d2);
  EXPECT_TRUE(b.pieces(c1)[from]);
  EXPECT_TRUE(b.pieces(pt1)[from]);
  EXPECT_TRUE(b.pieces(d1)[from]);
  EXPECT_TRUE(b.pieces(c2)[to]);
  EXPECT_TRUE(b.pieces(pt2)[to]);
  EXPECT_TRUE(b.pieces(d2)[to]);
  EXPECT_FALSE(b.pieces(c1)[to]);
  EXPECT_FALSE(b.pieces(pt1)[to]);
  EXPECT_FALSE(b.pieces(d1)[to]);
  EXPECT_FALSE(b.pieces(c2)[from]);
  EXPECT_FALSE(b.pieces(pt2)[from]);
  EXPECT_FALSE(b.pieces(d2)[from]);
  
  b.swapPiece(from, to);

  ASSERT_TRUE(b.pieceOn(from));
  ASSERT_TRUE(b.pieceOn(to));
  ASSERT_EQ(b.pieceOn(from), q);
  ASSERT_EQ(b.pieceOn(to), p);
  ASSERT_NE(c1, c2);
  ASSERT_NE(pt1, pt2);
  ASSERT_NE(d1, d2);
  EXPECT_TRUE(b.pieces(c1)[to]);
  EXPECT_TRUE(b.pieces(pt1)[to]);
  EXPECT_TRUE(b.pieces(d1)[to]);
  EXPECT_TRUE(b.pieces(c2)[from]);
  EXPECT_TRUE(b.pieces(pt2)[from]);
  EXPECT_TRUE(b.pieces(d2)[from]);
  EXPECT_FALSE(b.pieces(c1)[from]);
  EXPECT_FALSE(b.pieces(pt1)[from]);
  EXPECT_FALSE(b.pieces(d1)[from]);
  EXPECT_FALSE(b.pieces(c2)[to]);
  EXPECT_FALSE(b.pieces(pt2)[to]);
  EXPECT_FALSE(b.pieces(d2)[to]);
}

TEST_F(BoardTest, RotatePieceTest) {
  Board b;
  Piece p = make(SILVER, ANUBIS, NORTH);
  Square s = SQ_A1;
  b.addPiece(p, s);
  b.rotatePiece(s, POSITIVE);
  EXPECT_EQ(rotatePos(p), b.pieceOn(s));
  b.rotatePiece(s, POSITIVE);
  EXPECT_EQ(rotatePos(rotatePos(p)), b.pieceOn(s));
  b.rotatePiece(s, POSITIVE);
  EXPECT_EQ(rotatePos(rotatePos(rotatePos(p))), b.pieceOn(s));
  b.rotatePiece(s, POSITIVE);
  EXPECT_EQ(p, b.pieceOn(s));
  b.rotatePiece(s, NEGATIVE);
  EXPECT_EQ(rotateNeg(p), b.pieceOn(s));
  b.rotatePiece(s, NEGATIVE);
  EXPECT_EQ(rotateNeg(rotateNeg(p)), b.pieceOn(s));
  b.rotatePiece(s, NEGATIVE);
  EXPECT_EQ(rotateNeg(rotateNeg(rotateNeg(p))), b.pieceOn(s));
  b.rotatePiece(s, NEGATIVE);
  EXPECT_EQ(p, b.pieceOn(s));
}

INSTANTIATE_TEST_SUITE_P(
  BoardTests,
  BoardTestParam,
  ::testing::Values(
    std::make_tuple( //Classic
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
    ),
    std::make_tuple( //Dynasty
      "3PAP3X/4R5/3SAP3P/3p1p1S1P/p1s1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ NO_PIECE,
        /* C1 */ NO_PIECE,
        /* D1 */ SILVER_PYRAMID_WEST,
        /* E1 */ SILVER_ANUBIS_NORTH,
        /* F1 */ SILVER_PYRAMID_NORTH,
        /* G1 */ NO_PIECE,
        /* H1 */ NO_PIECE,
        /* I1 */ NO_PIECE,
        /* J1 */ SILVER_SPHINX_NORTH,
        /* A2 */ NO_PIECE,
        /* B2 */ NO_PIECE,
        /* C2 */ NO_PIECE,
        /* D2 */ NO_PIECE,
        /* E2 */ SILVER_PHARAOH_NORTH,
        /* F2 */ NO_PIECE,
        /* G2 */ NO_PIECE,
        /* H2 */ NO_PIECE,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ SILVER_SCARAB_EAST,
        /* E3 */ SILVER_ANUBIS_NORTH,
        /* F3 */ SILVER_PYRAMID_NORTH,
        /* G3 */ NO_PIECE,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ SILVER_PYRAMID_SOUTH,
        /* A4 */ NO_PIECE,
        /* B4 */ NO_PIECE,
        /* C4 */ NO_PIECE,
        /* D4 */ RED_PYRAMID_WEST,
        /* E4 */ NO_PIECE,
        /* F4 */ RED_PYRAMID_EAST,
        /* G4 */ NO_PIECE,
        /* H4 */ SILVER_SCARAB_NORTH,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_WEST,
        /* A5 */ RED_PYRAMID_EAST,
        /* B5 */ NO_PIECE,
        /* C5 */ RED_SCARAB_SOUTH,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_PYRAMID_WEST,
        /* F5 */ NO_PIECE,
        /* G5 */ SILVER_PYRAMID_EAST,
        /* H5 */ NO_PIECE,
        /* I5 */ NO_PIECE,
        /* J5 */ NO_PIECE,
        /* A6 */ RED_PYRAMID_NORTH,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ NO_PIECE,
        /* E6 */ RED_PYRAMID_SOUTH,
        /* F6 */ RED_ANUBIS_SOUTH,
        /* G6 */ RED_SCARAB_WEST,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ NO_PIECE,
        /* D7 */ NO_PIECE,
        /* E7 */ NO_PIECE,
        /* F7 */ RED_PHARAOH_SOUTH,
        /* G7 */ NO_PIECE,
        /* H7 */ NO_PIECE,
        /* I7 */ NO_PIECE,
        /* J7 */ NO_PIECE,
        /* A8 */ RED_SPHINX_SOUTH,
        /* B8 */ NO_PIECE,
        /* C8 */ NO_PIECE,
        /* D8 */ NO_PIECE,
        /* E8 */ RED_PYRAMID_SOUTH,
        /* F8 */ RED_ANUBIS_SOUTH,
        /* G8 */ RED_PYRAMID_EAST,
        /* H8 */ NO_PIECE,
        /* I8 */ NO_PIECE,
        /* J8 */ NO_PIECE,
      }
    ),
    std::make_tuple( //Imhotep
      "2SARA3X/0/3P2p3/pP2Sp2pP/pP2Ps2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ NO_PIECE,
        /* C1 */ SILVER_SCARAB_WEST,
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
        /* H2 */ NO_PIECE,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ SILVER_PYRAMID_SOUTH,
        /* E3 */ NO_PIECE,
        /* F3 */ NO_PIECE,
        /* G3 */ RED_PYRAMID_EAST,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ NO_PIECE,
        /* A4 */ RED_PYRAMID_EAST,
        /* B4 */ SILVER_PYRAMID_WEST,
        /* C4 */ NO_PIECE,
        /* D4 */ NO_PIECE,
        /* E4 */ SILVER_SCARAB_WEST,
        /* F4 */ RED_PYRAMID_WEST,
        /* G4 */ NO_PIECE,
        /* H4 */ NO_PIECE,
        /* I4 */ RED_PYRAMID_NORTH,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ SILVER_PYRAMID_SOUTH,
        /* C5 */ NO_PIECE,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_PYRAMID_EAST,
        /* F5 */ RED_SCARAB_EAST,
        /* G5 */ NO_PIECE,
        /* H5 */ NO_PIECE,
        /* I5 */ RED_PYRAMID_EAST,
        /* J5 */ SILVER_PYRAMID_WEST,
        /* A6 */ NO_PIECE,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ SILVER_PYRAMID_WEST,
        /* E6 */ NO_PIECE,
        /* F6 */ NO_PIECE,
        /* G6 */ RED_PYRAMID_NORTH,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ NO_PIECE,
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
        /* H8 */ RED_SCARAB_EAST,
        /* I8 */ NO_PIECE,
        /* J8 */ NO_PIECE,
      }
    ),
    std::make_tuple( //Osiris
      "pP1RP3sX/2PA3A2/3p6/p3SE3P/p3es3P/6P3/2a3ap2/xS3pr1pP nwnnenwnneeswsnenwwssesesses s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ RED_PYRAMID_NORTH,
        /* B1 */ SILVER_PYRAMID_WEST,
        /* C1 */ NO_PIECE,
        /* D1 */ SILVER_PHARAOH_NORTH,
        /* E1 */ SILVER_PYRAMID_NORTH,
        /* F1 */ NO_PIECE,
        /* G1 */ NO_PIECE,
        /* H1 */ NO_PIECE,
        /* I1 */ RED_SCARAB_EAST,
        /* J1 */ SILVER_SPHINX_NORTH,
        /* A2 */ NO_PIECE,
        /* B2 */ NO_PIECE,
        /* C2 */ SILVER_PYRAMID_WEST,
        /* D2 */ SILVER_ANUBIS_NORTH,
        /* E2 */ NO_PIECE,
        /* F2 */ NO_PIECE,
        /* G2 */ NO_PIECE,
        /* H2 */ SILVER_ANUBIS_NORTH,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ RED_PYRAMID_EAST,
        /* E3 */ NO_PIECE,
        /* F3 */ NO_PIECE,
        /* G3 */ NO_PIECE,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ NO_PIECE,
        /* A4 */ RED_PYRAMID_EAST,
        /* B4 */ NO_PIECE,
        /* C4 */ NO_PIECE,
        /* D4 */ NO_PIECE,
        /* E4 */ SILVER_SCARAB_SOUTH,
        /* F4 */ SILVER_EYE_OF_HORUS_WEST,
        /* G4 */ NO_PIECE,
        /* H4 */ NO_PIECE,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ NO_PIECE,
        /* C5 */ NO_PIECE,
        /* D5 */ NO_PIECE,
        /* E5 */ RED_EYE_OF_HORUS_EAST,
        /* F5 */ RED_SCARAB_NORTH,
        /* G5 */ NO_PIECE,
        /* H5 */ NO_PIECE,
        /* I5 */ NO_PIECE,
        /* J5 */ SILVER_PYRAMID_WEST,
        /* A6 */ NO_PIECE,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ NO_PIECE,
        /* E6 */ NO_PIECE,
        /* F6 */ NO_PIECE,
        /* G6 */ SILVER_PYRAMID_WEST,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ RED_ANUBIS_SOUTH,
        /* D7 */ NO_PIECE,
        /* E7 */ NO_PIECE,
        /* F7 */ NO_PIECE,
        /* G7 */ RED_ANUBIS_SOUTH,
        /* H7 */ RED_PYRAMID_EAST,
        /* I7 */ NO_PIECE,
        /* J7 */ NO_PIECE,
        /* A8 */ RED_SPHINX_SOUTH,
        /* B8 */ SILVER_SCARAB_EAST,
        /* C8 */ NO_PIECE,
        /* D8 */ NO_PIECE,
        /* E8 */ NO_PIECE,
        /* F8 */ RED_PYRAMID_SOUTH,
        /* G8 */ RED_PHARAOH_SOUTH,
        /* H8 */ NO_PIECE,
        /* I8 */ RED_PYRAMID_EAST,
        /* J8 */ SILVER_PYRAMID_SOUTH,
      }
    ),
    std::make_tuple( //Isis
      "1PRA5X/2AP3S1P/8s1/1P2ep1P1P/p1p1PE2p1/1S8/p1s3pa2/x5arp1 wnnnnnssnnwessnnwessnnssssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ SILVER_PYRAMID_WEST,
        /* C1 */ SILVER_PHARAOH_NORTH,
        /* D1 */ SILVER_ANUBIS_NORTH,
        /* E1 */ NO_PIECE,
        /* F1 */ NO_PIECE,
        /* G1 */ NO_PIECE,
        /* H1 */ NO_PIECE,
        /* I1 */ NO_PIECE,
        /* J1 */ SILVER_SPHINX_NORTH,
        /* A2 */ NO_PIECE,
        /* B2 */ NO_PIECE,
        /* C2 */ SILVER_ANUBIS_NORTH,
        /* D2 */ SILVER_PYRAMID_NORTH,
        /* E2 */ NO_PIECE,
        /* F2 */ NO_PIECE,
        /* G2 */ NO_PIECE,
        /* H2 */ SILVER_SCARAB_SOUTH,
        /* I2 */ NO_PIECE,
        /* J2 */ SILVER_PYRAMID_SOUTH,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ NO_PIECE,
        /* E3 */ NO_PIECE,
        /* F3 */ NO_PIECE,
        /* G3 */ NO_PIECE,
        /* H3 */ NO_PIECE,
        /* I3 */ RED_SCARAB_NORTH,
        /* J3 */ NO_PIECE,
        /* A4 */ NO_PIECE,
        /* B4 */ SILVER_PYRAMID_NORTH,
        /* C4 */ NO_PIECE,
        /* D4 */ NO_PIECE,
        /* E4 */ RED_EYE_OF_HORUS_WEST,
        /* F4 */ RED_PYRAMID_EAST,
        /* G4 */ NO_PIECE,
        /* H4 */ SILVER_PYRAMID_SOUTH,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ NO_PIECE,
        /* C5 */ RED_PYRAMID_NORTH,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_PYRAMID_WEST,
        /* F5 */ SILVER_EYE_OF_HORUS_EAST,
        /* G5 */ NO_PIECE,
        /* H5 */ NO_PIECE,
        /* I5 */ RED_PYRAMID_SOUTH,
        /* J5 */ NO_PIECE,
        /* A6 */ NO_PIECE,
        /* B6 */ SILVER_SCARAB_SOUTH,
        /* C6 */ NO_PIECE,
        /* D6 */ NO_PIECE,
        /* E6 */ NO_PIECE,
        /* F6 */ NO_PIECE,
        /* G6 */ NO_PIECE,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ RED_PYRAMID_NORTH,
        /* B7 */ NO_PIECE,
        /* C7 */ RED_SCARAB_NORTH,
        /* D7 */ NO_PIECE,
        /* E7 */ NO_PIECE,
        /* F7 */ NO_PIECE,
        /* G7 */ RED_PYRAMID_SOUTH,
        /* H7 */ RED_ANUBIS_SOUTH,
        /* I7 */ NO_PIECE,
        /* J7 */ NO_PIECE,
        /* A8 */ RED_SPHINX_SOUTH,
        /* B8 */ NO_PIECE,
        /* C8 */ NO_PIECE,
        /* D8 */ NO_PIECE,
        /* E8 */ NO_PIECE,
        /* F8 */ NO_PIECE,
        /* G8 */ RED_ANUBIS_SOUTH,
        /* H8 */ RED_PHARAOH_SOUTH,
        /* I8 */ RED_PYRAMID_EAST,
        /* J8 */ NO_PIECE,
      }
    ),
    std::make_tuple( //Classic2
      "2PARA3X/7P2/6p3/p1P1ES1p1P/p1P1Se1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0",
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
        /* E4 */ SILVER_EYE_OF_HORUS_WEST,
        /* F4 */ SILVER_SCARAB_SOUTH,
        /* G4 */ NO_PIECE,
        /* H4 */ RED_PYRAMID_NORTH,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ NO_PIECE,
        /* C5 */ SILVER_PYRAMID_SOUTH,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_SCARAB_NORTH,
        /* F5 */ RED_EYE_OF_HORUS_EAST,
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
        /* J8 */ NO_PIECE,
      }
    ),
    std::make_tuple( //Dynasty2
      "3PAP3X/4R5/3SAP3P/3p1p1E1P/p1e1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ NO_PIECE,
        /* C1 */ NO_PIECE,
        /* D1 */ SILVER_PYRAMID_WEST,
        /* E1 */ SILVER_ANUBIS_NORTH,
        /* F1 */ SILVER_PYRAMID_NORTH,
        /* G1 */ NO_PIECE,
        /* H1 */ NO_PIECE,
        /* I1 */ NO_PIECE,
        /* J1 */ SILVER_SPHINX_NORTH,
        /* A2 */ NO_PIECE,
        /* B2 */ NO_PIECE,
        /* C2 */ NO_PIECE,
        /* D2 */ NO_PIECE,
        /* E2 */ SILVER_PHARAOH_NORTH,
        /* F2 */ NO_PIECE,
        /* G2 */ NO_PIECE,
        /* H2 */ NO_PIECE,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ SILVER_SCARAB_EAST,
        /* E3 */ SILVER_ANUBIS_NORTH,
        /* F3 */ SILVER_PYRAMID_NORTH,
        /* G3 */ NO_PIECE,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ SILVER_PYRAMID_SOUTH,
        /* A4 */ NO_PIECE,
        /* B4 */ NO_PIECE,
        /* C4 */ NO_PIECE,
        /* D4 */ RED_PYRAMID_WEST,
        /* E4 */ NO_PIECE,
        /* F4 */ RED_PYRAMID_EAST,
        /* G4 */ NO_PIECE,
        /* H4 */ SILVER_EYE_OF_HORUS_NORTH,
        /* I4 */ NO_PIECE,
        /* J4 */ SILVER_PYRAMID_WEST,
        /* A5 */ RED_PYRAMID_EAST,
        /* B5 */ NO_PIECE,
        /* C5 */ RED_EYE_OF_HORUS_SOUTH,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_PYRAMID_WEST,
        /* F5 */ NO_PIECE,
        /* G5 */ SILVER_PYRAMID_EAST,
        /* H5 */ NO_PIECE,
        /* I5 */ NO_PIECE,
        /* J5 */ NO_PIECE,
        /* A6 */ RED_PYRAMID_NORTH,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ NO_PIECE,
        /* E6 */ RED_PYRAMID_SOUTH,
        /* F6 */ RED_ANUBIS_SOUTH,
        /* G6 */ RED_SCARAB_WEST,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ NO_PIECE,
        /* D7 */ NO_PIECE,
        /* E7 */ NO_PIECE,
        /* F7 */ RED_PHARAOH_SOUTH,
        /* G7 */ NO_PIECE,
        /* H7 */ NO_PIECE,
        /* I7 */ NO_PIECE,
        /* J7 */ NO_PIECE,
        /* A8 */ RED_SPHINX_SOUTH,
        /* B8 */ NO_PIECE,
        /* C8 */ NO_PIECE,
        /* D8 */ NO_PIECE,
        /* E8 */ RED_PYRAMID_SOUTH,
        /* F8 */ RED_ANUBIS_SOUTH,
        /* G8 */ RED_PYRAMID_EAST,
        /* H8 */ NO_PIECE,
        /* I8 */ NO_PIECE,
        /* J8 */ NO_PIECE,
      }
    ),
    std::make_tuple( //Imhotep2
      "2SARA3X/0/3P2p3/pP2Ep2pP/pP2Pe2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0",
      std::array<Piece, NUM_SQUARES> {
        /* A1 */ NO_PIECE,
        /* B1 */ NO_PIECE,
        /* C1 */ SILVER_SCARAB_WEST,
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
        /* H2 */ NO_PIECE,
        /* I2 */ NO_PIECE,
        /* J2 */ NO_PIECE,
        /* A3 */ NO_PIECE,
        /* B3 */ NO_PIECE,
        /* C3 */ NO_PIECE,
        /* D3 */ SILVER_PYRAMID_SOUTH,
        /* E3 */ NO_PIECE,
        /* F3 */ NO_PIECE,
        /* G3 */ RED_PYRAMID_EAST,
        /* H3 */ NO_PIECE,
        /* I3 */ NO_PIECE,
        /* J3 */ NO_PIECE,
        /* A4 */ RED_PYRAMID_EAST,
        /* B4 */ SILVER_PYRAMID_WEST,
        /* C4 */ NO_PIECE,
        /* D4 */ NO_PIECE,
        /* E4 */ SILVER_EYE_OF_HORUS_WEST,
        /* F4 */ RED_PYRAMID_WEST,
        /* G4 */ NO_PIECE,
        /* H4 */ NO_PIECE,
        /* I4 */ RED_PYRAMID_NORTH,
        /* J4 */ SILVER_PYRAMID_SOUTH,
        /* A5 */ RED_PYRAMID_NORTH,
        /* B5 */ SILVER_PYRAMID_SOUTH,
        /* C5 */ NO_PIECE,
        /* D5 */ NO_PIECE,
        /* E5 */ SILVER_PYRAMID_EAST,
        /* F5 */ RED_EYE_OF_HORUS_EAST,
        /* G5 */ NO_PIECE,
        /* H5 */ NO_PIECE,
        /* I5 */ RED_PYRAMID_EAST,
        /* J5 */ SILVER_PYRAMID_WEST,
        /* A6 */ NO_PIECE,
        /* B6 */ NO_PIECE,
        /* C6 */ NO_PIECE,
        /* D6 */ SILVER_PYRAMID_WEST,
        /* E6 */ NO_PIECE,
        /* F6 */ NO_PIECE,
        /* G6 */ RED_PYRAMID_NORTH,
        /* H6 */ NO_PIECE,
        /* I6 */ NO_PIECE,
        /* J6 */ NO_PIECE,
        /* A7 */ NO_PIECE,
        /* B7 */ NO_PIECE,
        /* C7 */ NO_PIECE,
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
        /* H8 */ RED_SCARAB_EAST,
        /* I8 */ NO_PIECE,
        /* J8 */ NO_PIECE,
      }
    )
  )
);