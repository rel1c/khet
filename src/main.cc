#include <iostream>
#include <map>
#include <string>
#include "board.h"

static void show(Board&);

int main(int argc, const char **argv) {
  Board b;

  std::cout << "Dynasty" << std::endl;
  b.setPkn(
      "3PAP3X/4R5/3SAP3P/3p1p1S1P/p1s1P1P3/p3pas3/5r4/x3pap3 wnnnnennswenweswensswsssse s 0"
  );
  show(b);

  b = Board();
  std::cout << "Imhotep" << std::endl;
  b.setPkn(
      "2SARA3X/0/3P2p3/pP2Sp2pP/pP2Ps2pP/3P2p3/0/x3aras2 wnnnnseewwwnsnseeewwnsssse s 0"
  );
  show(b);

  b = Board();
  std::cout << "Osiris" << std::endl;
  b.setPkn(
      "pP1RP3sX/2PA3A2/3p6/p3SE3P/p3es3P/6P3/2a3ap2/xS3pr1pP nwnnenwnneeswsnenwwssesesses s 0"
  );
  show(b);

  b = Board();
  std::cout << "Isis" << std::endl;
  b.setPkn(
      "1PRA5X/2AP3S1P/8s1/1P2ep1P1P/p1p1PE2p1/1S8/p1s3pa2/x5arp1 wnnnnnssnnwessnnwessnnssssse s 0"
  );
  show(b);
  return 0;
}

static void show(Board& b) {
  std::map<int, std::string> PieceStr{
    {0 ,"NO_PIECE"},
    {36,"SILVER_ANUBIS_NORTH"},
    {37,"SILVER_ANUBIS_EAST"},
    {38,"SILVER_ANUBIS_SOUTH"},
    {39,"SILVER_ANUBIS_WEST"},
    {56,"SILVER_EYE_OF_HORUS_NORTH"},
    {57,"SILVER_EYE_OF_HORUS_EAST"},
    {58,"SILVER_EYE_OF_HORUS_SOUTH"},
    {59,"SILVER_EYE_OF_HORUS_WEST"},
    {44,"SILVER_PHARAOH_NORTH"},
    {45,"SILVER_PHARAOH_EAST"},
    {46,"SILVER_PHARAOH_SOUTH"},
    {47,"SILVER_PHARAOH_WEST"},
    {48,"SILVER_PYRAMID_NORTH"},
    {49,"SILVER_PYRAMID_EAST"},
    {50,"SILVER_PYRAMID_SOUTH"},
    {51,"SILVER_PYRAMID_WEST"},
    {52,"SILVER_SCARAB_NORTH"},
    {53,"SILVER_SCARAB_EAST"},
    {54,"SILVER_SCARAB_SOUTH"},
    {55,"SILVER_SCARAB_WEST"},
    {40,"SILVER_SPHINX_NORTH"},
    {41,"SILVER_SPHINX_EAST"},
    {42,"SILVER_SPHINX_SOUTH"},
    {43,"SILVER_SPHINX_WEST"},
    {68,"RED_ANUBIS_NORTH"},
    {69,"RED_ANUBIS_EAST"},
    {70,"RED_ANUBIS_SOUTH"},
    {71,"RED_ANUBIS_WEST"},
    {88,"RED_EYE_OF_HORUS_NORTH"},
    {89,"RED_EYE_OF_HORUS_EAST"},
    {90,"RED_EYE_OF_HORUS_SOUTH"},
    {91,"RED_EYE_OF_HORUS_WEST"},
    {76,"RED_PHARAOH_NORTH"},
    {77,"RED_PHARAOH_EAST"},
    {78,"RED_PHARAOH_SOUTH"},
    {79,"RED_PHARAOH_WEST"},
    {80,"RED_PYRAMID_NORTH"},
    {81,"RED_PYRAMID_EAST"},
    {82,"RED_PYRAMID_SOUTH"},
    {83,"RED_PYRAMID_WEST"},
    {84,"RED_SCARAB_NORTH"},
    {85,"RED_SCARAB_EAST"},
    {86,"RED_SCARAB_SOUTH"},
    {87,"RED_SCARAB_WEST"},
    {72,"RED_SPHINX_NORTH"},
    {73,"RED_SPHINX_EAST"},
    {74,"RED_SPHINX_SOUTH"},
    {75,"RED_SPHINX_WEST"}
  };
  std::array<std::string, 80> sc{
    "/* A1 */ ",
    "/* B1 */ ",
    "/* C1 */ ",
    "/* D1 */ ",
    "/* E1 */ ",
    "/* F1 */ ",
    "/* G1 */ ",
    "/* H1 */ ",
    "/* I1 */ ",
    "/* J1 */ ",
    "/* A2 */ ",
    "/* B2 */ ",
    "/* C2 */ ",
    "/* D2 */ ",
    "/* E2 */ ",
    "/* F2 */ ",
    "/* G2 */ ",
    "/* H2 */ ",
    "/* I2 */ ",
    "/* J2 */ ",
    "/* A3 */ ",
    "/* B3 */ ",
    "/* C3 */ ",
    "/* D3 */ ",
    "/* E3 */ ",
    "/* F3 */ ",
    "/* G3 */ ",
    "/* H3 */ ",
    "/* I3 */ ",
    "/* J3 */ ",
    "/* A4 */ ",
    "/* B4 */ ",
    "/* C4 */ ",
    "/* D4 */ ",
    "/* E4 */ ",
    "/* F4 */ ",
    "/* G4 */ ",
    "/* H4 */ ",
    "/* I4 */ ",
    "/* J4 */ ",
    "/* A5 */ ",
    "/* B5 */ ",
    "/* C5 */ ",
    "/* D5 */ ",
    "/* E5 */ ",
    "/* F5 */ ",
    "/* G5 */ ",
    "/* H5 */ ",
    "/* I5 */ ",
    "/* J5 */ ",
    "/* A6 */ ",
    "/* B6 */ ",
    "/* C6 */ ",
    "/* D6 */ ",
    "/* E6 */ ",
    "/* F6 */ ",
    "/* G6 */ ",
    "/* H6 */ ",
    "/* I6 */ ",
    "/* J6 */ ",
    "/* A7 */ ",
    "/* B7 */ ",
    "/* C7 */ ",
    "/* D7 */ ",
    "/* E7 */ ",
    "/* F7 */ ",
    "/* G7 */ ",
    "/* H7 */ ",
    "/* I7 */ ",
    "/* J7 */ ",
    "/* A8 */ ",
    "/* B8 */ ",
    "/* C8 */ ",
    "/* D8 */ ",
    "/* E8 */ ",
    "/* F8 */ ",
    "/* G8 */ ",
    "/* H8 */ ",
    "/* I8 */ ",
    "/* J8 */ ",
  };
  std::cout << "-----------------------------" << std::endl;
  for (int i = 0; i < NUM_SQUARES; i++) {
    Square s = static_cast<Square>(i);
    Piece p = b.pieceOn(s);
    std::cout << sc[i] << PieceStr[p] << "," << std::endl;
  }
}
