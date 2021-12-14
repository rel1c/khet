#include "bitboard.h"
#include "board.h"
#include "layout.h"
#include "move.h"
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
class BoardTest : public::testing::Test {};

// Initialize a board from a PKN string
TEST_F(BoardTest, PknSquaresTest) {
  std::string pkn = "";
}

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

// Display the board in a convenient format
TEST_F(BoardTest, DisplayTest) {
  Board b(CLASSIC);
  ASSERT_EQ(b.getAllPieces().count(), 26);
  CoutRedirect cr;
  b.display();
  std::string output = cr.getString();
  std::string expect = 
    "8 x...arap.. s...ssse.. SILVER\n"
    "7 ..p....... ..s....... turn: 0\n"
    "6 ...P...... ...w......\n"
    "5 p.P.ss.p.P n.s.ne.e.w\n"
    "4 p.P.SS.p.P e.w.ws.n.s\n"
    "3 ......p... ......e...\n"
    "2 .......P.. .......n..\n"
    "1 ..PARA...X ..wnnn...n\n"
    "  abcdefghij abcdefghij\n";
  EXPECT_EQ(output, expect);
}

using pkn_tup_t = std::tuple<std::string, SquareVec, std::string>;
class PknBoardTestsParam : public ::testing::TestWithParam <pkn_tup_t> {
public:
  std::string pkn;
  SquareVec sv;
  std::string expect;
  unsigned int n_pieces;
};

TEST_P(PknBoardTestsParam, PknBoardTest) {
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

/*
// Test the mapping of bitboard notation to actual indices
TEST_F(BoardTest, ConstructorClassicRedTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.red_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000111100\n"
    "0010000000\n"
    "0000000000\n"
    "1000110100\n"
    "1000000100\n"
    "0000001000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSilverTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.silver_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0001000000\n"
    "0010000001\n"
    "0010110001\n"
    "0000000000\n"
    "0000000100\n"
    "0011110001\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicNorthTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.north_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "1000100000\n"
    "0000000100\n"
    "0000000000\n"
    "0000000100\n"
    "0001110001\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicEastTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.east_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000100\n"
    "0000000000\n"
    "0000000000\n"
    "0000010100\n"
    "1000000000\n"
    "0000001000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSouthTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.south_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000111000\n"
    "0010000000\n"
    "0000000000\n"
    "0010000000\n"
    "0000010001\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicWestTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.west_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0001000000\n"
    "0000000001\n"
    "0010100000\n"
    "0000000000\n"
    "0000000000\n"
    "0010000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicAnubisTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.anubis_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000101000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0001010000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicPharaohTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.pharaoh_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000010000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000100000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicPyramidTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.pyramid_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000100\n"
    "0010000000\n"
    "0001000000\n"
    "1010000101\n"
    "1010000101\n"
    "0000001000\n"
    "0000000100\n"
    "0010000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicScarabTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.scarab_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000110000\n"
    "0000110000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n";
  EXPECT_EQ(output, expect);
}

TEST_F(BoardTest, ConstructorClassicSphinxTest) {
  Board classic = Board(CLASSIC);
  std::string output, expect;
  testing::internal::CaptureStdout();
  displayBitboard(classic.sphinx_);
  output = testing::internal::GetCapturedStdout();
  expect = 
    "1000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000000\n"
    "0000000001\n";
  EXPECT_EQ(output, expect);
}

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
  GTEST_SKIP();//TODO
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
