#include "movegen.h"
#include "util.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <iostream>
#include <streambuf>
#include <string>
#include <tuple>
#include <vector>

namespace khet {

class CoutRedirect {

public:
    CoutRedirect() {
      old = std::cout.rdbuf(buffer.rdbuf()); // redirect cout to buffer stream
    }

    std::string getString() {
      return buffer.str(); // get string
    }

    ~CoutRedirect() {
      std::cout.rdbuf(old); // reverse redirect
    }
private:
    std::stringstream buffer;
    std::streambuf* old;
};

/// Bitboard Tests /////////////////////////////////////////////////////////////

class BitboardTest : public::testing::Test {};

TEST_F(BitboardTest, SizeTest) {
  Bitboard bb;
  EXPECT_EQ(sizeof(bb), 16) << "Bitboard is 16 bytes long";
}

// Test the mapping of bitboard notation to actual indices
TEST_F(BitboardTest, SquareIndexTest) {
  ASSERT_EQ(A1, 0);
  ASSERT_EQ(J8, 79);
}

// Test creating initializing a bitboard from a notation vector
TEST_F(BitboardTest, InitBoardTest) {
  Bitboard bb;
  ASSERT_FALSE(bb.all());
  bb = initBitboard(std::vector<Square> {A1, E5, J8});
  EXPECT_EQ(bb[A1], 1);
  EXPECT_EQ(bb[E5], 1);
  EXPECT_EQ(bb[J8], 1);
}

// Test the file values
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

// Test the rank values
TEST_F(BitboardTest, RanksTest) {
  std::vector<Bitboard> ranks = {RANK_1, RANK_2, RANK_3, RANK_4,
                                 RANK_5, RANK_6, RANK_7, RANK_8};
  ASSERT_EQ(NRANKS, ranks.size());
  for (int i = 0; i < NRANKS; i++) {
    Bitboard rank = ranks[i];
    for (int j = 0; j < NFILES; j++) {
      EXPECT_EQ(rank[i * NFILES + j], 1);
    }
  }
}

// Test the square values
TEST_F(BitboardTest, SquaresTest) {
  ASSERT_EQ(NSQUARES, SQUARES.size());
  for (int i = 0; i < NSQUARES; i++) {
    Bitboard bb = SQUARES[i];
    ASSERT_EQ(bb.count(), 1);
    EXPECT_EQ(bb[i], 1);
  }
}

// Display the bitboard in a convenient format
TEST_F(BitboardTest, DisplayTest) {
  Bitboard bb = initBitboard(std::vector<Square> {
    A1, B2, C3, D6, E6, F4, G2, G7, H5, I8, J1, J6
  });
  CoutRedirect cr;
  displayBitboard(bb);
  std::string output = cr.getString();
  std::string expect = 
    "8 0000000010\n"
    "7 0000001000\n"
    "6 0001100001\n"
    "5 0000000100\n"
    "4 0000010000\n"
    "3 0010000000\n"
    "2 0100001000\n"
    "1 1000000001\n"
    "  abcdefghij\n";
  EXPECT_EQ(output, expect);
}

/// Board Tests ////////////////////////////////////////////////////////////////

class BoardTest : public::testing::Test {
public:
  void SetUp() {
    board_c = Board(CLASSIC);
    board_d = Board(DYNASTY);
    board_i = Board(IMHOTEP);
  }
protected:
  Board board_c;
  Board board_d;
  Board board_i;
};

// Initialize a board from a PKN string
TEST_F(BoardTest, PknBoardTest) {
  std::string pkn = "5RS2X/5A4/5S3p/0/0/p3s5/4a5/x2sr5 nsnnssnnssns s 0";
  Board b(pkn);
  ASSERT_EQ(b.getAllPieces().count(), 12);
  EXPECT_TRUE(b.isPieceAt(F1));
  EXPECT_TRUE(b.isPieceAt(G1));
  EXPECT_TRUE(b.isPieceAt(J1));
  EXPECT_TRUE(b.isPieceAt(F2));
  EXPECT_TRUE(b.isPieceAt(F3));
  EXPECT_TRUE(b.isPieceAt(J3));
  EXPECT_TRUE(b.isPieceAt(A6));
  EXPECT_TRUE(b.isPieceAt(E6));
  EXPECT_TRUE(b.isPieceAt(E7));
  EXPECT_TRUE(b.isPieceAt(A8));
  EXPECT_TRUE(b.isPieceAt(D8));
  EXPECT_TRUE(b.isPieceAt(E8));
}

TEST_F(BoardTest, getColorClassicTest) {
  Bitboard red_c = initBitboard(std::vector<Square> {
    A4, A5, A8, C7, E5, E8, F5, F8, G3, G8, H4, H5, H8
  });
  Bitboard silver_c = initBitboard(std::vector<Square> {
    C1, C4, C5, D1, D6, E1, E4, F1, F4, H2, J1, J4, J5
  });
  EXPECT_EQ(red_c, board_c.getColor(RED));
  EXPECT_EQ(silver_c, board_c.getColor(SILVER));
}

TEST_F(BoardTest, getColorDynastyTest) {
  Bitboard red_d = initBitboard(std::vector<Square> {
    D4, F4, A5, C5, A6, E6, F6, G6, F7, A8, E8, F8, G8
  });
  Bitboard silver_d = initBitboard(std::vector<Square> {
    D1, E1, F1, J1, E2, D3, E3, F3, J3, H4, J4, E5, G5
  });
  EXPECT_EQ(red_d, board_d.getColor(RED));
  EXPECT_EQ(silver_d, board_d.getColor(SILVER));
}

TEST_F(BoardTest, getColorImhotepTest) {
  Bitboard red_i = initBitboard(std::vector<Square> {
    G3, A4, F4, I4, A5, F5, I5, G6, A8, E8, F8, G8, H8
  });
  Bitboard silver_i = initBitboard(std::vector<Square> {
    C1, D1, E1, F1, J1, D3, B4, E4, J4, B5, E5, J5, D6
  });
  EXPECT_EQ(red_i, board_i.getColor(RED));
  EXPECT_EQ(silver_i, board_i.getColor(SILVER));
}

TEST_F(BoardTest, getDirectionClassicTest) {
  Bitboard north_c = initBitboard(std::vector<Square> {
    A5, D1, E1, E5, F1, H2, H4, J1
  });
  Bitboard east_c = initBitboard(std::vector<Square> {
    A4, F5, G3, H5, H8
  });
  Bitboard south_c = initBitboard(std::vector<Square> {
    A8, C5, C7, E8, F4, F8, G8, J4
  });
  Bitboard west_c = initBitboard(std::vector<Square> {
    C1, C4, D6, E4, J5
  });
  EXPECT_EQ(north_c, board_c.getDirection(NORTH));
  EXPECT_EQ(east_c, board_c.getDirection(EAST));
  EXPECT_EQ(south_c, board_c.getDirection(SOUTH));
  EXPECT_EQ(west_c, board_c.getDirection(WEST));
}

TEST_F(BoardTest, getDirectionDynastyTest) {
  Bitboard north_d = initBitboard(std::vector<Square> {
    A6, E1, E2, E3, F1, F3, H4, J1
  });
  Bitboard east_d = initBitboard(std::vector<Square> {
    A5, D3, F4, G5, G8
  });
  Bitboard south_d = initBitboard(std::vector<Square> {
    A8, C5, E6, E8, F6, F7, F8, J3
  });
  Bitboard west_d = initBitboard(std::vector<Square> {
    D1, D4, E5, G6, J4
  });
  EXPECT_EQ(north_d, board_d.getDirection(NORTH));
  EXPECT_EQ(east_d, board_d.getDirection(EAST));
  EXPECT_EQ(south_d, board_d.getDirection(SOUTH));
  EXPECT_EQ(west_d, board_d.getDirection(WEST));
}

TEST_F(BoardTest, getDirectionImhotepTest) {
  Bitboard north_i = initBitboard(std::vector<Square> {
    A5, D1, E1, F1, G6, I4, J1
  });
  Bitboard east_i = initBitboard(std::vector<Square> {
    A4, E5, F5, G3, H8, I5
  });
  Bitboard south_i = initBitboard(std::vector<Square> {
    A8, B5, D3, E8, F8, G8, J4
  });
  Bitboard west_i = initBitboard(std::vector<Square> {
    B4, C1, D6, E4, F4, J5
  });
  EXPECT_EQ(north_i, board_i.getDirection(NORTH));
  EXPECT_EQ(east_i, board_i.getDirection(EAST));
  EXPECT_EQ(south_i, board_i.getDirection(SOUTH));
  EXPECT_EQ(west_i, board_i.getDirection(WEST));
}

TEST_F(BoardTest, getPieceClassicTest) {
  Bitboard anubis_c = initBitboard(std::vector<Square> {
    D1, E8, F1, G8
  });
  Bitboard pharaoh_c = initBitboard(std::vector<Square> {
    E1, F8
  });
  Bitboard pyramid_c = initBitboard(std::vector<Square> {
    A4, A5, C1, C4, C5, C7, D6, G3, H2, H4, H5, H8, J4, J5
  });
  Bitboard scarab_c = initBitboard(std::vector<Square> {
    E4, E5, F4, F5
  });
  Bitboard sphinx_c = initBitboard(std::vector<Square> {
    A8, J1
  });
  EXPECT_EQ(anubis_c, board_c.getPiece(ANUBIS));
  EXPECT_EQ(pharaoh_c, board_c.getPiece(PHARAOH));
  EXPECT_EQ(pyramid_c, board_c.getPiece(PYRAMID));
  EXPECT_EQ(scarab_c, board_c.getPiece(SCARAB));
  EXPECT_EQ(sphinx_c, board_c.getPiece(SPHINX));
}

TEST_F(BoardTest, getPieceDynastyTest) {
  Bitboard anubis_d = initBitboard(std::vector<Square> {
    E1, E3, F6, F8
  });
  Bitboard pharaoh_d = initBitboard(std::vector<Square> {
    E2, F7
  });
  Bitboard pyramid_d = initBitboard(std::vector<Square> {
    A5, A6, D1, D4, E5, E6, E8, F1, F3, F4, G5, G8, J3, J4
  });
  Bitboard scarab_d = initBitboard(std::vector<Square> {
    C5, D3, G6, H4
  });
  Bitboard sphinx_d = initBitboard(std::vector<Square> {
    A8, J1
  });
  EXPECT_EQ(anubis_d, board_d.getPiece(ANUBIS));
  EXPECT_EQ(pharaoh_d, board_d.getPiece(PHARAOH));
  EXPECT_EQ(pyramid_d, board_d.getPiece(PYRAMID));
  EXPECT_EQ(scarab_d, board_d.getPiece(SCARAB));
  EXPECT_EQ(sphinx_d, board_d.getPiece(SPHINX));
}

TEST_F(BoardTest, getPieceImhotepTest) {
  Bitboard anubis_i = initBitboard(std::vector<Square> {
    D1, E8, F1, G8
  });
  Bitboard pharaoh_i = initBitboard(std::vector<Square> {
    E1, F8
  });
  Bitboard pyramid_i = initBitboard(std::vector<Square> {
    A4, A5, B4, B5, D3, D6, E5, F4, G3, G6, I4, I5, J4, J5
  });
  Bitboard scarab_i = initBitboard(std::vector<Square> {
    C1, E4, F5, H8
  });
  Bitboard sphinx_i = initBitboard(std::vector<Square> {
    A8, J1
  });
  EXPECT_EQ(anubis_i, board_i.getPiece(ANUBIS));
  EXPECT_EQ(pharaoh_i, board_i.getPiece(PHARAOH));
  EXPECT_EQ(pyramid_i, board_i.getPiece(PYRAMID));
  EXPECT_EQ(scarab_i, board_i.getPiece(SCARAB));
  EXPECT_EQ(sphinx_i, board_i.getPiece(SPHINX));
}

TEST_F(BoardTest, getColorAtClassicTest) {
  SquareVec red_c = {
    A4, A5, A8, C7, E5, E8, F5, F8, G3, G8, H4, H5, H8
  };
  SquareVec silver_c = {
    C1, C4, C5, D1, D6, E1, E4, F1, F4, H2, J1, J4, J5
  };
  Bitboard red_bb_c = board_c.getColor(RED);
  for (auto s : red_c) {
    EXPECT_TRUE(red_bb_c[s]);
  }
  Bitboard silver_bb_c = board_c.getColor(SILVER);
  for (auto s : silver_c) {
    EXPECT_TRUE(silver_bb_c[s]);
  }
}

TEST_F(BoardTest, getColorAtDynastyTest) {
  SquareVec red_d = {
    D4, F4, A5, C5, A6, E6, F6, G6, F7, A8, E8, F8, G8
  };
  SquareVec silver_d = {
    D1, E1, F1, J1, E2, D3, E3, F3, J3, H4, J4, E5, G5
  };
  Bitboard red_bb_d = board_d.getColor(RED);
  for (auto s : red_d) {
    EXPECT_TRUE(red_bb_d[s]);
  }
  Bitboard silver_bb_d = board_d.getColor(SILVER);
  for (auto s : silver_d) {
    EXPECT_TRUE(silver_bb_d[s]);
  }
}

TEST_F(BoardTest, getColorAtImhotepTest) {
  SquareVec red_i = {
    G3, A4, F4, I4, A5, F5, I5, G6, A8, E8, F8, G8, H8
  };
  SquareVec silver_i = {
    C1, D1, E1, F1, J1, D3, B4, E4, J4, B5, E5, J5, D6
  };
  Bitboard red_bb_i = board_i.getColor(RED);
  for (auto s : red_i) {
    EXPECT_TRUE(red_bb_i[s]);
  }
  Bitboard silver_bb_i = board_i.getColor(SILVER);
  for (auto s : silver_i) {
    EXPECT_TRUE(silver_bb_i[s]);
  }
}

TEST_F(BoardTest, getPieceAtClassicTest) {
  SquareVec anubis_c = {
    D1, E8, F1, G8
  };
  SquareVec pharaoh_c = {
    E1, F8
  };
  SquareVec pyramid_c = {
    A4, A5, C1, C4, C5, C7, D6, G3, H2, H4, H5, H8, J4, J5
  };
  SquareVec scarab_c = {
    E4, E5, F4, F5
  };
  SquareVec sphinx_c = {
    A8, J1
  };
  Bitboard anubis_bb_c = board_c.getPiece(ANUBIS);
  for (auto s : anubis_c) {
    EXPECT_TRUE(anubis_bb_c[s]);
  }
  Bitboard pharaoh_bb_c = board_c.getPiece(PHARAOH);
  for (auto s : pharaoh_c) {
    EXPECT_TRUE(pharaoh_bb_c[s]);
  }
  Bitboard pyramid_bb_c = board_c.getPiece(PYRAMID);
  for (auto s : pyramid_c) {
    EXPECT_TRUE(pyramid_bb_c[s]);
  }
  Bitboard scarab_bb_c = board_c.getPiece(SCARAB);
  for (auto s : scarab_c) {
    EXPECT_TRUE(scarab_bb_c[s]);
  }
  Bitboard sphinx_bb_c = board_c.getPiece(SPHINX);
  for (auto s : sphinx_c) {
    EXPECT_TRUE(sphinx_bb_c[s]);
  }
}

TEST_F(BoardTest, getPieceAtDynastyTest) {
  SquareVec anubis_d = {
    E1, E3, F6, F8
  };
  SquareVec pharaoh_d = {
    E2, F7
  };
  SquareVec pyramid_d = {
    A5, A6, D1, D4, E5, E6, E8, F1, F3, F4, G5, G8, J3, J4
  };
  SquareVec scarab_d = {
    C5, D3, G6, H4
  };
  SquareVec sphinx_d = {
    A8, J1
  };
  Bitboard anubis_bb_d = board_d.getPiece(ANUBIS);
  for (auto s : anubis_d) {
    EXPECT_TRUE(anubis_bb_d[s]);
  }
  Bitboard pharaoh_bb_d = board_d.getPiece(PHARAOH);
  for (auto s : pharaoh_d) {
    EXPECT_TRUE(pharaoh_bb_d[s]);
  }
  Bitboard pyramid_bb_d = board_d.getPiece(PYRAMID);
  for (auto s : pyramid_d) {
    EXPECT_TRUE(pyramid_bb_d[s]);
  }
  Bitboard scarab_bb_d = board_d.getPiece(SCARAB);
  for (auto s : scarab_d) {
    EXPECT_TRUE(scarab_bb_d[s]);
  }
  Bitboard sphinx_bb_d = board_d.getPiece(SPHINX);
  for (auto s : sphinx_d) {
    EXPECT_TRUE(sphinx_bb_d[s]);
  }
}

TEST_F(BoardTest, getPieceAtImhotepTest) {
  SquareVec anubis_i = {
    D1, E8, F1, G8
  };
  SquareVec pharaoh_i = {
    E1, F8
  };
  SquareVec pyramid_i = {
    A4, A5, B4, B5, D3, D6, E5, F4, G3, G6, I4, I5, J4, J5
  };
  SquareVec scarab_i = {
    C1, E4, F5, H8
  };
  SquareVec sphinx_i = {
    A8, J1
  };
  Bitboard anubis_bb_i = board_i.getPiece(ANUBIS);
  for (auto s : anubis_i) {
    EXPECT_TRUE(anubis_bb_i[s]);
  }
  Bitboard pharaoh_bb_i = board_i.getPiece(PHARAOH);
  for (auto s : pharaoh_i) {
    EXPECT_TRUE(pharaoh_bb_i[s]);
  }
  Bitboard pyramid_bb_i = board_i.getPiece(PYRAMID);
  for (auto s : pyramid_i) {
    EXPECT_TRUE(pyramid_bb_i[s]);
  }
  Bitboard scarab_bb_i = board_i.getPiece(SCARAB);
  for (auto s : scarab_i) {
    EXPECT_TRUE(scarab_bb_i[s]);
  }
  Bitboard sphinx_bb_i = board_i.getPiece(SPHINX);
  for (auto s : sphinx_i) {
    EXPECT_TRUE(sphinx_bb_i[s]);
  }
}

TEST_F(BoardTest, getAllPiecesClassicTest) {
  Bitboard expect_all_c = initBitboard(
    SquareVec {
      A4, A5, A8, C1, C4, C5, C7, D1, D6, E1, E4, E5, E8,
      F1, F4, F5, F8, G3, G8, H2, H4, H5, H8, J1, J4, J5
    }
  );
  Bitboard actual_all_c = board_c.getAllPieces();
  EXPECT_EQ(expect_all_c, actual_all_c);
}

TEST_F(BoardTest, getAllPiecesDynastyTest) {
  Bitboard expect_all_d = initBitboard(
    SquareVec {
      A5, A6, A8, C5, D1, D3, D4, E1, E2, E3, E5, E6, E8,
      F1, F3, F4, F6, F7, F8, G5, G6, G8, H4, J1, J3, J4
    }
  );
  Bitboard actual_all_d = board_d.getAllPieces();
  EXPECT_EQ(expect_all_d, actual_all_d);
}

TEST_F(BoardTest, getAllPiecesImhotepTest) {
  Bitboard expect_all_i = initBitboard(
    SquareVec {
      A4, A5, A8, B4, B5, C1, D1, D3, D6, E1, E4, E5, E8,
      F1, F4, F5, F8, G3, G6, G8, H8, I4, I5, J1, J4, J5
    }
  );
  Bitboard actual_all_i = board_i.getAllPieces();
  EXPECT_EQ(expect_all_i, actual_all_i);
}

TEST_F(BoardTest, getSwappableClassicTest) {
  Bitboard expect_swap_c = initBitboard(
    SquareVec {
      A4, A5, C1, C4, C5, C7, D1, D6, E8,
      F1, G3, G8, H2, H4, H5, H8, J4, J5
    }
  );
  Bitboard actual_swap_c = board_c.getSwappable();
  EXPECT_EQ(expect_swap_c, actual_swap_c);
}

TEST_F(BoardTest, getSwappableDynastyTest) {
  Bitboard expect_swap_d = initBitboard(
    SquareVec {
      A5, A6, D1, D4, E1, E3, E5, E6, E8,
      F1, F3, F4, F6, F8, G5, G8, J3, J4
    }
  );
  Bitboard actual_swap_d = board_d.getSwappable();
  EXPECT_EQ(expect_swap_d, actual_swap_d);
}

TEST_F(BoardTest, getSwappableImhotepTest) {
  Bitboard expect_swap_i = initBitboard(
    SquareVec {
      A4, A5, B4, B5, D1, D3, D6, E5, E8,
      F1, F4, G3, G6, G8, I4, I5, J4, J5
    }
  );
  Bitboard actual_swap_i = board_i.getSwappable();
  EXPECT_EQ(expect_swap_i, actual_swap_i);
}

TEST_F(BoardTest, getPlayerTest) {
  std::string pkn_s = "5RS2X/5A4/5S3p/0/0/p3s5/4a5/x2sr5 nsnnssnnssns s 0";
  Board bs(pkn_s);
  std::string pkn_r = "5RS2X/5A4/5S3p/0/0/p3s5/4a5/x2sr5 nsnnssnnssns r 0";
  Board br(pkn_r);
  EXPECT_EQ(bs.getPlayer(), SILVER);
  EXPECT_EQ(br.getPlayer(), RED);
}

using pkn_tup_t = std::tuple<std::string, SquareVec, std::string>;
class PknBoardTestsParam : public ::testing::TestWithParam <pkn_tup_t> {
public:
  std::string pkn;
  SquareVec sv;
  std::string expect;
  unsigned int n_pieces;
};

TEST_P(PknBoardTestsParam, PknBoardDisplayTest) {
  pkn = std::get<0>(GetParam());
  sv = std::get<1>(GetParam());
  expect = std::get<2>(GetParam());
  Board b(pkn);
  n_pieces = sv.size();
  EXPECT_EQ(b.getAllPieces().count(), n_pieces);
  CoutRedirect cr;
  b.display();
  std::string output = cr.getString();
  EXPECT_EQ(output, expect);
}

INSTANTIATE_TEST_SUITE_P(
  PknBoardTests,
  PknBoardTestsParam,
  ::testing::Values(
    std::make_tuple( //classic layout
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0",
      SquareVec {C1,D1,E1,F1,J1,H2,G3,A4,C4,E4,F4,H4,J4,A5,C5,E5,F5,H5,J5,D6,C7,A8,E8,F8,G8,H8},
      "8 x...arap.. s...ssse.. SILVER\n"
      "7 ..p....... ..s....... turn: 0\n"
      "6 ...P...... ...w......\n"
      "5 p.P.ss.p.P n.s.ne.e.w\n"
      "4 p.P.SS.p.P e.w.ws.n.s\n"
      "3 ......p... ......e...\n"
      "2 .......P.. .......n..\n"
      "1 ..PARA...X ..wnnn...n\n"
      "  abcdefghij abcdefghij\n"
    ),
    std::make_tuple( //dynasty layout
      "3PAP3X/4R5/3SAP3P/3p1p1S1P/p1s1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0",
      SquareVec {D1,E1,F1,J1,E2,D3,E3,F3,J3,D4,F4,H4,J4,A5,C5,E5,G5,A6,E6,F6,G6,F7,A8,E8,F8,G8},
      "8 x...pap... s...sse... SILVER\n"
      "7 .....r.... .....s.... turn: 0\n"
      "6 p...pas... n...ssw...\n"
      "5 p.s.P.P... e.s.w.e...\n"
      "4 ...p.p.S.P ...w.e.n.w\n"
      "3 ...SAP...P ...enn...s\n"
      "2 ....R..... ....n.....\n"
      "1 ...PAP...X ...wnn...n\n"
      "  abcdefghij abcdefghij\n"
    ),
    std::make_tuple( //imhotep layout
      "2SARA3X/0/3P2p3/pP2Sp2pP/pP2Ps2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0",
      SquareVec {C1,D1,E1,F1,J1,D3,G3,A4,B4,E4,F4,I4,J4,A5,B5,E5,F5,I5,J5,D6,G6,A8,E8,F8,G8,H8},
      "8 x...aras.. s...ssse.. SILVER\n"
      "7 .......... .......... turn: 0\n"
      "6 ...P..p... ...w..n...\n"
      "5 pP..Ps..pP ns..ee..ew\n"
      "4 pP..Sp..pP ew..ww..ns\n"
      "3 ...P..p... ...s..e...\n"
      "2 .......... ..........\n"
      "1 ..SARA...X ..wnnn...n\n"
      "  abcdefghij abcdefghij\n"
    ),
    std::make_tuple( //minimal layout
      "5SRS1X/0/0/0/0/0/0/x1srs5 nnnnssss r 99",
      SquareVec {F1,G1,H1,J1,A8,C8,D8,E8},
      "8 x.srs..... s.sss..... RED\n"
      "7 .......... .......... turn: 99\n"
      "6 .......... ..........\n"
      "5 .......... ..........\n"
      "4 .......... ..........\n"
      "3 .......... ..........\n"
      "2 .......... ..........\n"
      "1 .....SRS.X .....nnn.n\n"
      "  abcdefghij abcdefghij\n"
    //),
    //std::make_tuple( //empty layout
    //  "0/0/0/0/0/0/0/0 r 2",
    //  SquareVec {},
    //  "8 .......... .......... RED\n"
    //  "7 .......... .......... turn: 2\n"
    //  "6 .......... ..........\n"
    //  "5 .......... ..........\n"
    //  "4 .......... ..........\n"
    //  "3 .......... ..........\n"
    //  "2 .......... ..........\n"
    //  "1 .......... ..........\n"
    //  "  abcdefghij abcdefghij\n"
    )
  )
);

/// Action Tests ///////////////////////////////////////////////////////////////
/*
class ActionTest : public::testing::Test {};

TEST_F(ActionTest, SizeTest) {
  Action act;
  ASSERT_EQ(sizeof(act), 4) << "Action is 4 bytes long";
  EXPECT_EQ(sizeof(act), sizeof(int)) << "Action is same size as int";
}

// Test ...
TEST_F(ActionTest, OutStreamTest) {
  //Action act;
  //testing::internal::CaptureStdout();
  //std::cout << act;
  //std::string output = testing::internal::GetCapturedStdout();
  //std::string expect = "";
  //EXPECT_EQ(output, expect);
}

/// Gamestate Tests ////////////////////////////////////////////////////////////

class GamestateTest : public::testing::Test {};

// Test ...
TEST_F(GamestateTest, GenMovesTest) {
  Gamestate gs;
  Board b = gs.getBoard();
  gs.genMoves(G3); // red pyramid south, classic board
  Action mov1(G3, G4);
  Action mov2(G3, F3);
  Action mov3(G3, H3);
  Action mov4(G3, F2);
  Action mov5(G3, G2);
  using namespace testing;
  EXPECT_THAT(gs.getActions(), Contains(mov1));
  EXPECT_THAT(gs.getActions(), Contains(mov2));
  EXPECT_THAT(gs.getActions(), Contains(mov3));
  EXPECT_THAT(gs.getActions(), Contains(mov4));
  EXPECT_THAT(gs.getActions(), Contains(mov5));
}

// Test ...
TEST_F(GamestateTest, GenSwapsTest) {
  //TODO Could use a more thorough test with custom layout
  Gamestate gs;
  Board b = gs.getBoard();
  ASSERT_TRUE(b.scarab_[F4] & b.south_[F4]); // silver scarab south, classic
  gs.genSwaps(F4);
  Action mov1(F4, G3, true);
  using namespace testing;
  EXPECT_THAT(gs.getActions(), Contains(mov1));
}

// Test ...
TEST_F(GamestateTest, GenRotationsTest) {
  Gamestate gs;
  Board b = gs.getBoard();
  ASSERT_TRUE(b.pharaoh_[E1] & b.north_[E1]); // silver pharaoh north, classic
  gs.genRotations(E1);
  Action mov1(E1, NORTH, WEST);
  Action mov2(E1, NORTH, EAST);
  using namespace testing;
  EXPECT_THAT(gs.getActions(), Contains(mov1));
  EXPECT_THAT(gs.getActions(), Contains(mov2));
}

// Test ...
TEST_F(GamestateTest, GenSphinxActionTest) {
  Gamestate gs;
  Board b = gs.getBoard();
  ASSERT_TRUE(b.sphinx_[J1] & b.north_[J1]); // silver sphinx north, classic
  gs.genSphinxActions(J1);
  ASSERT_TRUE(b.sphinx_[A8] & b.south_[A8]); // red sphinx south, classic
  gs.genSphinxActions(A8);
  Action mov1(J1, NORTH, WEST);
  Action mov2(A8, SOUTH, EAST);
  using namespace testing;
  EXPECT_THAT(gs.getActions(), Contains(mov1));
  EXPECT_THAT(gs.getActions(), Contains(mov2));
}

// Test ...
TEST_F(GamestateTest, GenActionsTest) {
  Gamestate gs;
  Board b = gs.getBoard();
  std::vector<Action> actions;
  std::vector<Square> squares {
    C1, D1, E1, F1, J1, H2, C4, E4, F4, J4, C5, J5, D6
  };
  // wow look I rewrote it!
  // how's that for a test case?
  for (Square s : squares) {
    if (b.sphinx_[s]) {
      gs.genSphinxActions(s);
      continue;
    }
    if (b.scarab_[s]) {
      gs.genSwaps(s);
    }
    gs.genMoves(s);
    gs.genRotations(s);
  }
  actions = gs.getActions();
  gs = Gamestate();
  ASSERT_TRUE(gs.getActions().size() == 0);
  gs.genActions(SILVER); // first silver turn, classic
  EXPECT_EQ(actions, gs.getActions());
}
// TODO manually add moves for each square, then check for containment and pop!
*/

} // namespace khet
