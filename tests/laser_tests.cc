#include <gtest/gtest.h>

#include "laser.h"

class LaserTest : public::testing::Test {};

TEST_F(LaserTest, BasicFireTest) {
  Board b;
  std::string pkn = "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0";
  b.setPkn(pkn);
  Laser l;
  Capture expect = NO_CAPTURE;
  Capture result = l.fire(b, SQ_J2, NORTH);
  EXPECT_EQ(expect, result);
  expect = makeCapture(SILVER_ANUBIS_NORTH, SQ_F1);
  result = l.fire(b, SQ_I1, WEST);
  EXPECT_EQ(expect, result);
  pkn = "3P2sp1X/1R6P1/1r8/0/0/6P2P/3s4p1/x6S1S nwnwnwsewessen s 0";
  b = Board(); // TODO setPkn should clear the board!
  b.setPkn(pkn);
  expect = makeCapture(SILVER_PHARAOH_NORTH, SQ_B2);
  result = l.fire(b, SQ_I1, WEST);
  EXPECT_EQ(expect, result);
}
