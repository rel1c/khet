#include "laser.h"

namespace khet {

static const BounceTable genBounceTable();

const BounceTable Laser::_bounces = genBounceTable();

static const BounceTable genBounceTable() {
  BounceTable bt;
  //TODO currently stubbed with nonsense
  for (auto s : squares) {
    for (auto d : {NORTH, EAST, SOUTH, WEST}) {
      bt[s][d] = Bitboard(0);
    }
  }
  return bt;
}

} // namespace khet
