#include "laser.h"
#include <iostream>

namespace khet {

static ReflectTable genReflectTable();
static Bitboard genReflectPath(Square, Direction);

const ReflectTable Laser::_reflections = genReflectTable();

const OrderTable _reflectOrder = {
  LSB,
  LSB,
  MSB,
  MSB
};

/**
 * @brief Fires the laser and returns the outcome, a bitboard serving as a
 * negative bit mask for an eliminated piece.
 * @param b The board
 */
Bitboard fire(const Board& b) {
  
}

/**
 * @brief Debugging function to display reflection look-up table.
 */
void Laser::showReflectTable() const {
  for (auto s : squares) {
    for (auto d : {NORTH, EAST, SOUTH, WEST}) {
      std::cout << "[" << squareStrings[s] << "][";
      std::cout << directionStrings[d] << "]:" << std::endl;
      displayBitboard(_reflections[s][d]);
    }
  }
}

/**
 * @brief Generate reflection look-up table at compile time.
 */
static ReflectTable genReflectTable() {
  ReflectTable bt;
  bt.fill({});
  for (auto s : squares) {
    for (auto d : {NORTH, EAST, SOUTH, WEST}) {
      bt[s][d] = genReflectPath(s, d);
    }
  }
  return bt;
}

/**
 * @brief Helper function for generating the reflection table. Traces out a
 * laser path from each square to an edge and stores it at the squares location
 * in the table.
 */
static Bitboard genReflectPath(Square s, Direction d) {
  Bitboard bb = 0;
  Square t = s;
  while (true) {
    if (d == NORTH && !RANK_8[t]) {
      t = static_cast<Square>(t + NFILES);
    }
    else if (d == EAST && !FILE_J[t]) {
      t = static_cast<Square>(t + 1);
    }
    else if (d == SOUTH && !RANK_1[t]) {
      t = static_cast<Square>(t - NFILES);
    }
    else if (d == WEST && !FILE_A[t]) {
      t = static_cast<Square>(t - 1);
    }
    else {
      break;
    }
    bb.flip(t);
  }
  return bb;
}

} // namespace khet
