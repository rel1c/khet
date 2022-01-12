#include <string>
#include <iostream>
#include "bitboard.h"

namespace khet {

const std::array<Square, NSQUARES> squares {
  A1, B1, C1, D1, E1, F1, G1, H1, I1, J1,
  A2, B2, C2, D2, E2, F2, G2, H2, I2, J2,
  A3, B3, C3, D3, E3, F3, G3, H3, I3, J3,
  A4, B4, C4, D4, E4, F4, G4, H4, I4, J4,
  A5, B5, C5, D5, E5, F5, G5, H5, I5, J5,
  A6, B6, C6, D6, E6, F6, G6, H6, I6, J6,
  A7, B7, C7, D7, E7, F7, G7, H7, I7, J7,
  A8, B8, C8, D8, E8, F8, G8, H8, I8, J8,
};

const std::array<std::string, NSQUARES> squareStrings {
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "i1", "j1",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "i2", "j2",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "i3", "j3",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "i4", "j4",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "i5", "j5",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "i6", "j6",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "i7", "j7",
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "i8", "j8",
};

const Bitboard FILE_A = initBitboard(SquareVec {
  A1, A2, A3, A4, A5, A6, A7, A8
});
const Bitboard FILE_B = FILE_A << 1;
const Bitboard FILE_C = FILE_A << 2;
const Bitboard FILE_D = FILE_A << 3;
const Bitboard FILE_E = FILE_A << 4;
const Bitboard FILE_F = FILE_A << 5;
const Bitboard FILE_G = FILE_A << 6;
const Bitboard FILE_H = FILE_A << 7;
const Bitboard FILE_I = FILE_A << 8;
const Bitboard FILE_J = FILE_A << 9;

const Bitboard RANK_1 = initBitboard(SquareVec {
  A1, B1, C1, D1, E1, F1, G1, H1, I1, J1
});
const Bitboard RANK_2 = RANK_1 << (NFILES * 1);
const Bitboard RANK_3 = RANK_1 << (NFILES * 2);
const Bitboard RANK_4 = RANK_1 << (NFILES * 3);
const Bitboard RANK_5 = RANK_1 << (NFILES * 4);
const Bitboard RANK_6 = RANK_1 << (NFILES * 5);
const Bitboard RANK_7 = RANK_1 << (NFILES * 6);
const Bitboard RANK_8 = RANK_1 << (NFILES * 7);

const std::array<Bitboard, NSQUARES> SQUARES {
  FILE_A & RANK_1,
  FILE_B & RANK_1,
  FILE_C & RANK_1,
  FILE_D & RANK_1,
  FILE_E & RANK_1,
  FILE_F & RANK_1,
  FILE_G & RANK_1,
  FILE_H & RANK_1,
  FILE_I & RANK_1,
  FILE_J & RANK_1,

  FILE_A & RANK_2,
  FILE_B & RANK_2,
  FILE_C & RANK_2,
  FILE_D & RANK_2,
  FILE_E & RANK_2,
  FILE_F & RANK_2,
  FILE_G & RANK_2,
  FILE_H & RANK_2,
  FILE_I & RANK_2,
  FILE_J & RANK_2,

  FILE_A & RANK_3,
  FILE_B & RANK_3,
  FILE_C & RANK_3,
  FILE_D & RANK_3,
  FILE_E & RANK_3,
  FILE_F & RANK_3,
  FILE_G & RANK_3,
  FILE_H & RANK_3,
  FILE_I & RANK_3,
  FILE_J & RANK_3,

  FILE_A & RANK_4,
  FILE_B & RANK_4,
  FILE_C & RANK_4,
  FILE_D & RANK_4,
  FILE_E & RANK_4,
  FILE_F & RANK_4,
  FILE_G & RANK_4,
  FILE_H & RANK_4,
  FILE_I & RANK_4,
  FILE_J & RANK_4,

  FILE_A & RANK_5,
  FILE_B & RANK_5,
  FILE_C & RANK_5,
  FILE_D & RANK_5,
  FILE_E & RANK_5,
  FILE_F & RANK_5,
  FILE_G & RANK_5,
  FILE_H & RANK_5,
  FILE_I & RANK_5,
  FILE_J & RANK_5,

  FILE_A & RANK_6,
  FILE_B & RANK_6,
  FILE_C & RANK_6,
  FILE_D & RANK_6,
  FILE_E & RANK_6,
  FILE_F & RANK_6,
  FILE_G & RANK_6,
  FILE_H & RANK_6,
  FILE_I & RANK_6,
  FILE_J & RANK_6,

  FILE_A & RANK_7,
  FILE_B & RANK_7,
  FILE_C & RANK_7,
  FILE_D & RANK_7,
  FILE_E & RANK_7,
  FILE_F & RANK_7,
  FILE_G & RANK_7,
  FILE_H & RANK_7,
  FILE_I & RANK_7,
  FILE_J & RANK_7,

  FILE_A & RANK_8,
  FILE_B & RANK_8,
  FILE_C & RANK_8,
  FILE_D & RANK_8,
  FILE_E & RANK_8,
  FILE_F & RANK_8,
  FILE_G & RANK_8,
  FILE_H & RANK_8,
  FILE_I & RANK_8,
  FILE_J & RANK_8,
};

/**
 * @brief Initialize a bitboard with a list of board squares.
 * @param v The list (vector) of squares
 */
Bitboard initBitboard(const SquareVec& v) {
  Bitboard bb;
  for (auto& i : v) {
    bb.set(i);
  }
  return bb;
};

/** 
 * @brief Display a bitboard as a Khet board, boardered by rank and file 
 * notation, with starting square in the lower left, as seen by the silver
 * player.
 * @param bb The bitboard
 */
void displayBitboard(const Bitboard& bb) {
  std::string bb_str = bb.to_string();
  for (int i = NRANKS; i > 0; i--) {
    std::cout << i << " ";
    for (int j = 0; j < NFILES; j++) {
      std::cout << bb[(i-1) * NFILES + j];
    }
    std::cout << "\n";
  }
  std::cout << "  abcdefghij" << std::endl;
}

} // namespace khet
