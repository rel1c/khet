#include "piece.h"

#ifndef MOVE_H_
#define MOVE_H_

const unsigned int NUM_SQUARES = 80;

enum Square : unsigned int {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1, SQ_I1, SQ_J1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2, SQ_I2, SQ_J2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3, SQ_I3, SQ_J3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4, SQ_I4, SQ_J4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5, SQ_I5, SQ_J5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6, SQ_I6, SQ_J6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7, SQ_I7, SQ_J7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8, SQ_I8, SQ_J8,
  SQ_NONE
};
using Move = unsigned int;

const unsigned int SQ_MASK = 0b1111111;

// Moves are 16 bits wide, composed of four fields
// [from : 7][rotate : 1][swap : 1][to/rotation : 7]
// If a move has the rotate flag set, it is expected
// to have its lowest bit treated as a value for
// positive or negative rotation, else the first 7 bits
// are to be treated as a board square.

constexpr Move makeMove(Square from, Square to, bool swap=false) {
  return from << 9 | swap << 7 | to;
}

constexpr Move makeMove(Square from, Rotation rotate) {
  return from << 9 | 1 << 8 | rotate;
}

inline Square getFrom(Move m) {
  return Square(m >> 9);
}

inline Square getTo(Move m) {
  assert(~m & 1 << 8); // not a rotation
  return Square(m & SQ_MASK);
}

inline bool isRotate(Move m) {
  return m & 1 << 8;
}

inline bool isSwap(Move m) {
  return m & 1 << 7;
}

inline Rotation getRotation(Move m) {
  assert(m & 1 << 8); // is a rotation
  return Rotation(m & 1);
}

#endif
