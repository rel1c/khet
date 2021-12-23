#include "laser.h"
#include <iostream>

namespace khet {

static const BounceTable genBounceTable();
static const Bitboard genBouncePath(const Square, const Direction);

const BounceTable Laser::_bounces = genBounceTable();

void Laser::showBounceTable() const {
  for (auto s : squares) {
    for (auto d : directions) {
      std::cout << "s:" << s << std::endl;
      std::cout << "d:" << d << std::endl;
      displayBitboard(_bounces[s][d]);
    }
  }
}

static const BounceTable genBounceTable() {
  BounceTable bt;
  for (auto s : squares) {
    for (auto d : directions) {
      bt[s][d] = genBouncePath(s, d);
    }
  }
  return (const BounceTable) bt;
}

static const Bitboard genBouncePath(const Square s, const Direction d) {
  static const Bitboard edge = FILE_A | FILE_J | RANK_1 | RANK_8;
  Bitboard bb;
  Square t = s;
  while (true) {
    if (edge[t]) {
      break;
    }

    if (d == NORTH) {
      t = static_cast<Square>(t + NFILES);
    }
    else if (d == EAST) {
      t = static_cast<Square>(t + 1);
    }
    else if (d == SOUTH) {
      t = static_cast<Square>(t - NFILES);
    }
    else {
      t = static_cast<Square>(t - 1);
    }
    bb.flip(t);
  }
  return (const Bitboard) bb;
}

} // namespace khet
