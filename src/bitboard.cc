#include <string>
#include <iostream>
#include "bitboard.h"

namespace khet {

const Bitboard FILE_A = initBitboard(Squares {
  A1, A2, A3, A4, A5, A6, A7, A8
});
const Bitboard FILE_B = initBitboard(Squares {
  B1, B2, B3, B4, B5, B6, B7, B8
});
const Bitboard FILE_C = initBitboard(Squares {
  C1, C2, C3, C4, C5, C6, C7, C8
});
const Bitboard FILE_D = initBitboard(Squares {
  D1, D2, D3, D4, D5, D6, D7, D8
});
const Bitboard FILE_E = initBitboard(Squares {
  E1, E2, E3, E4, E5, E6, E7, E8
});
const Bitboard FILE_F = initBitboard(Squares {
  F1, F2, F3, F4, F5, F6, F7, F8
});
const Bitboard FILE_G = initBitboard(Squares {
  G1, G2, G3, G4, G5, G6, G7, G8
});
const Bitboard FILE_H = initBitboard(Squares {
  H1, H2, H3, H4, H5, H6, H7, H8
});
const Bitboard FILE_I = initBitboard(Squares {
  I1, I2, I3, I4, I5, I6, I7, I8
});
const Bitboard FILE_J = initBitboard(Squares {
  J1, J2, J3, J4, J5, J6, J7, J8
});

const Bitboard RANK_1 = initBitboard(Squares {
  A1, B1, C1, D1, E1, F1, G1, H1, I1, J1
});
const Bitboard RANK_2 = initBitboard(Squares {
  A2, B2, C2, D2, E2, F2, G2, H2, I2, J2
});
const Bitboard RANK_3 = initBitboard(Squares {
  A3, B3, C3, D3, E3, F3, G3, H3, I3, J3
});
const Bitboard RANK_4 = initBitboard(Squares {
  A4, B4, C4, D4, E4, F4, G4, H4, I4, J4
});
const Bitboard RANK_5 = initBitboard(Squares {
  A5, B5, C5, D5, E5, F5, G5, H5, I5, J5
});
const Bitboard RANK_6 = initBitboard(Squares {
  A6, B6, C6, D6, E6, F6, G6, H6, I6, J6
});
const Bitboard RANK_7 = initBitboard(Squares {
  A7, B7, C7, D7, E7, F7, G7, H7, I7, J7
});
const Bitboard RANK_8 = initBitboard(Squares {
  A8, B8, C8, D8, E8, F8, G8, H8, I8, J8
});

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
Bitboard initBitboard(const Squares& v) {
  Bitboard bb;
  for (auto& i : v) {
    bb.set(i);
  }
  return bb;
};

/** 
 * @brief Display a bitboard as a Khet board, with starting square in the
 * lower left, as seen by the silver player.
 * @param bb The bitboard.
 */
void displayBitboard(const Bitboard& bb){
  std::string bb_str = bb.to_string();
  std::string out_str = "";
  for (int i = NRANKS - 1; i >= 0; i--) {
    for (int j = 0; j < NFILES; j++) {
      std::cout << bb[i * NFILES + j];
    }
    std::cout << std::endl;
  }
}

} // namespace khet
