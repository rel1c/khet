#include <gtest/gtest.h>

#include "test_util.h"
#include "movegen.h"

class MoveGenTest : public::testing::Test {};
class MoveGenTestParam : public ::testing::TestWithParam<std::tuple<std::string, Moves>> {};

TEST_F(MoveGenTest, InitMoveBBTest) {
  for (int i = 0; i < NUM_SQUARES; i++) {
    // flags for i-11, i-10, i-9, i-1, i+1, i+9, i+10, i+11
    //             0     1     2    3    4    5     6     7
    int flags[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    if (i % 10 == 0) // left
      flags[0] = flags[3] = flags[5] = 0;
    if (i % 10 == 9) // right
      flags[2] = flags[4] = flags[7] = 0;
    if (i < 10) // bottom
      flags[0] = flags[1] = flags[2] = 0;
    if (i >= 70) // top
      flags[5] = flags[6] = flags[7] = 0;
    Bitboard bb;
    if (flags[0]) bb[i-11] = true;
    if (flags[1]) bb[i-10] = true;
    if (flags[2]) bb[i-9] = true;
    if (flags[3]) bb[i-1] = true;
    if (flags[4]) bb[i+1] = true;
    if (flags[5]) bb[i+9] = true;
    if (flags[6]) bb[i+10] = true;
    if (flags[7]) bb[i+11] = true;
    ASSERT_EQ(bb.count(), MOVE_BB[i].count());
    EXPECT_EQ(bb, MOVE_BB[i]);
  }
}

TEST_F(MoveGenTest, InitMoveListTest) {
  //This is implicitly verified by InitMoveBBTest and BBToVecTest
  return;
}

TEST_P(MoveGenTestParam, GenTest) {
  Board b;
  std::string pkn = std::get<0>(GetParam());
  Moves expect_moves = std::get<1>(GetParam());
  Moves output_moves;
  b.setPkn(pkn);
  gen(b, output_moves);
  EXPECT_EQ(expect_moves, output_moves);
}

INSTANTIATE_TEST_SUITE_P(
  MoveGenTests,
  MoveGenTestParam,
  ::testing::Values(
    std::make_tuple( //Classic
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0",
      Moves {
        makeMove(SQ_C1, SQ_B1),
        makeMove(SQ_C1, SQ_B2),
        makeMove(SQ_C1, SQ_C2),
        makeMove(SQ_C1, SQ_D2),
        makeMove(SQ_C1, POSITIVE),
        makeMove(SQ_C1, NEGATIVE),
        makeMove(SQ_D1, SQ_C2),
        makeMove(SQ_D1, SQ_D2),
        makeMove(SQ_D1, SQ_E2),
        makeMove(SQ_D1, POSITIVE),
        makeMove(SQ_D1, NEGATIVE),
        makeMove(SQ_E1, SQ_D2),
        makeMove(SQ_E1, SQ_E2),
        makeMove(SQ_E1, SQ_F2),
        makeMove(SQ_E1, POSITIVE),
        makeMove(SQ_E1, NEGATIVE),
        makeMove(SQ_F1, SQ_G1),
        makeMove(SQ_F1, SQ_E2),
        makeMove(SQ_F1, SQ_F2),
        makeMove(SQ_F1, SQ_G2),
        makeMove(SQ_F1, POSITIVE),
        makeMove(SQ_F1, NEGATIVE),
        makeMove(SQ_J1, NEGATIVE),
        makeMove(SQ_H2, SQ_G1),
        makeMove(SQ_H2, SQ_H1),
        makeMove(SQ_H2, SQ_G2),
        makeMove(SQ_H2, SQ_I2),
        makeMove(SQ_H2, SQ_H3),
        makeMove(SQ_H2, SQ_I3),
        makeMove(SQ_H2, POSITIVE),
        makeMove(SQ_H2, NEGATIVE),
        makeMove(SQ_C4, SQ_B3),
        makeMove(SQ_C4, SQ_C3),
        makeMove(SQ_C4, SQ_D3),
        makeMove(SQ_C4, SQ_B4),
        makeMove(SQ_C4, SQ_D4),
        makeMove(SQ_C4, SQ_B5),
        makeMove(SQ_C4, SQ_D5),
        makeMove(SQ_C4, POSITIVE),
        makeMove(SQ_C4, NEGATIVE),
        makeMove(SQ_E4, SQ_D3),
        makeMove(SQ_E4, SQ_E3),
        makeMove(SQ_E4, SQ_F3),
        makeMove(SQ_E4, SQ_D4),
        makeMove(SQ_E4, SQ_D5),
        makeMove(SQ_E4, POSITIVE),
        makeMove(SQ_E4, NEGATIVE),
        makeMove(SQ_F4, SQ_G3, true),
        makeMove(SQ_F4, SQ_E3),
        makeMove(SQ_F4, SQ_F3),
        makeMove(SQ_F4, SQ_G4),
        makeMove(SQ_F4, SQ_G5),
        makeMove(SQ_F4, POSITIVE),
        makeMove(SQ_F4, NEGATIVE),
        makeMove(SQ_J4, SQ_I3),
        makeMove(SQ_J4, SQ_J3),
        makeMove(SQ_J4, SQ_I4),
        makeMove(SQ_J4, SQ_I5),
        makeMove(SQ_J4, POSITIVE),
        makeMove(SQ_J4, NEGATIVE),
        makeMove(SQ_C5, SQ_B4),
        makeMove(SQ_C5, SQ_D4),
        makeMove(SQ_C5, SQ_B5),
        makeMove(SQ_C5, SQ_D5),
        makeMove(SQ_C5, SQ_B6),
        makeMove(SQ_C5, SQ_C6),
        makeMove(SQ_C5, POSITIVE),
        makeMove(SQ_C5, NEGATIVE),
        makeMove(SQ_J5, SQ_I4),
        makeMove(SQ_J5, SQ_I5),
        makeMove(SQ_J5, SQ_I6),
        makeMove(SQ_J5, SQ_J6),
        makeMove(SQ_J5, POSITIVE),
        makeMove(SQ_J5, NEGATIVE),
        makeMove(SQ_D6, SQ_D5),
        makeMove(SQ_D6, SQ_C6),
        makeMove(SQ_D6, SQ_E6),
        makeMove(SQ_D6, SQ_D7),
        makeMove(SQ_D6, SQ_E7),
        makeMove(SQ_D6, POSITIVE),
        makeMove(SQ_D6, NEGATIVE)
      }
    )
  )
);
/*
    ),
    std::make_tuple( //Dynasty
      "3PAP3X/4R5/3SAP3P/3p1p1S1P/p1s1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Imhotep
      "2SARA3X/0/3P2p3/pP2Sp2pP/pP2Ps2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Osiris
      "pP1RP3sX/2PA3A2/3p6/p3SE3P/p3es3P/6P3/2a3ap2/xS3pr1pP nwnnenwnneeswsnenwwssesesses s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Isis
      "1PRA5X/2AP3S1P/8s1/1P2ep1P1P/p1p1PE2p1/1S8/p1s3pa2/x5arp1 wnnnnnssnnwessnnwessnnssssse s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Classic2
      "2PARA3X/7P2/6p3/p1P1ES1p1P/p1P1Se1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Dynasty2
      "3PAP3X/4R5/3SAP3P/3p1p1E1P/p1e1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0",
      std::vector<Move>{
      }
    ),
    std::make_tuple( //Imhotep2
      "2SARA3X/0/3P2p3/pP2Ep2pP/pP2Pe2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0",
      std::vector<Move>{
      }
*/
