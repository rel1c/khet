#include "bitboard.h"
#include <string>
#include <iostream>

namespace khet {

const Bitboard FILE_A = initBitboard(std::vector<int> {A1, A2, A3, A4, A5, A6, A7, A8});
const Bitboard FILE_B = initBitboard(std::vector<int> {B1, B2, B3, B4, B5, B6, B7, B8});
const Bitboard FILE_C = initBitboard(std::vector<int> {C1, C2, C3, C4, C5, C6, C7, C8});
const Bitboard FILE_D = initBitboard(std::vector<int> {D1, D2, D3, D4, D5, D6, D7, D8});
const Bitboard FILE_E = initBitboard(std::vector<int> {E1, E2, E3, E4, E5, E6, E7, E8});
const Bitboard FILE_F = initBitboard(std::vector<int> {F1, F2, F3, F4, F5, F6, F7, F8});
const Bitboard FILE_G = initBitboard(std::vector<int> {G1, G2, G3, G4, G5, G6, G7, G8});
const Bitboard FILE_H = initBitboard(std::vector<int> {H1, H2, H3, H4, H5, H6, H7, H8});
const Bitboard FILE_I = initBitboard(std::vector<int> {I1, I2, I3, I4, I5, I6, I7, I8});
const Bitboard FILE_J = initBitboard(std::vector<int> {J1, J2, J3, J4, J5, J6, J7, J8});

const Bitboard RANK_1 = initBitboard(std::vector<int> {A1, B1, C1, D1, E1, F1, G1, H1, I1, J1});
const Bitboard RANK_2 = initBitboard(std::vector<int> {A2, B2, C2, D2, E2, F2, G2, H2, I2, J2});
const Bitboard RANK_3 = initBitboard(std::vector<int> {A3, B3, C3, D3, E3, F3, G3, H3, I3, J3});
const Bitboard RANK_4 = initBitboard(std::vector<int> {A4, B4, C4, D4, E4, F4, G4, H4, I4, J4});
const Bitboard RANK_5 = initBitboard(std::vector<int> {A5, B5, C5, D5, E5, F5, G5, H5, I5, J5});
const Bitboard RANK_6 = initBitboard(std::vector<int> {A6, B6, C6, D6, E6, F6, G6, H6, I6, J6});
const Bitboard RANK_7 = initBitboard(std::vector<int> {A7, B7, C7, D7, E7, F7, G7, H7, I7, J7});
const Bitboard RANK_8 = initBitboard(std::vector<int> {A8, B8, C8, D8, E8, F8, G8, H8, I8, J8});

Bitboard initBitboard(const std::vector<int>& v) {
  Bitboard bb;
  for (auto& i : v) {
    bb.set(i);
  }
  return bb;
};

void displayBitboard(Bitboard& bb) {
  std::string bb_str = bb.to_string();
  std::string out_str = "";
  //for (int i = 0; i < FILES; i++) {
  int j = 0;
  for (int i = bb_str.length() - 1; i >= 0; i--) {
    if (j++ % 10 == 0) { //TODO magic number
      out_str += '\n';
    }
    out_str = bb_str[i] + out_str;
  }
  std::cout << out_str << std::endl;
}

} // namespace khet
