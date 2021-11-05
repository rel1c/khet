#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <array>
#include <bitset>
#include <vector>

namespace khet {

const int NBITS = 128;
const int NFILES = 10;
const int NRANKS = 8;

using Bitboard = std::bitset <NBITS>;

enum Square {
  A1, B1, C1, D1, E1, F1, G1, H1, I1, J1,
  A2, B2, C2, D2, E2, F2, G2, H2, I2, J2,
  A3, B3, C3, D3, E3, F3, G3, H3, I3, J3,
  A4, B4, C4, D4, E4, F4, G4, H4, I4, J4,
  A5, B5, C5, D5, E5, F5, G5, H5, I5, J5,
  A6, B6, C6, D6, E6, F6, G6, H6, I6, J6,
  A7, B7, C7, D7, E7, F7, G7, H7, I7, J7,
  A8, B8, C8, D8, E8, F8, G8, H8, I8, J8,
};

extern const Bitboard FILE_A;
extern const Bitboard FILE_B;
extern const Bitboard FILE_C;
extern const Bitboard FILE_D;
extern const Bitboard FILE_E;
extern const Bitboard FILE_F;
extern const Bitboard FILE_G;
extern const Bitboard FILE_H;
extern const Bitboard FILE_I;
extern const Bitboard FILE_J;

extern const Bitboard RANK_1;
extern const Bitboard RANK_2;
extern const Bitboard RANK_3;
extern const Bitboard RANK_4;
extern const Bitboard RANK_5;
extern const Bitboard RANK_6;
extern const Bitboard RANK_7;
extern const Bitboard RANK_8;

Bitboard initBitboard(const std::vector<int>& v);

} // namespace khet

#endif
