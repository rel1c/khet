#include "laser.h"
#include <iostream>
#include <map>

namespace khet {

const std::array<std::array<Direction, NDIRECTIONS>, NDIRECTIONS> REFLECTS {
  {
    {WEST, SOUTH, EAST, NORTH},
    {EAST, NORTH, WEST, SOUTH},
    {WEST, SOUTH, EAST, NORTH},
    {EAST, NORTH, WEST, SOUTH}
  }
};

const std::array<std::array<Direction, NDIRECTIONS>, NDIRECTIONS> PYRAMID_REFLECTS {
};

Laser::Laser() {
  fire(Board());
}

Laser::Laser(const Board& b) {
  fire(b);
}

bool Laser::didHit() {
  return _hit;
}

Bitboard Laser::getPath() {
  return _path;
}

Square Laser::getWhere() {
  return _where;
}

/**
 * @brief Fires the laser... 
 * @param b The board
 */
void Laser::fire(const Board& b) {
  // Prepare to fire...
  Square s = (b.getPlayer() == SILVER) ? SILVER_LASER : RED_LASER;
  Direction d = b.getDirectionAt(s);
  _hit = false;
  _path = 0;
  _where = s;
  // Fire away!
  Bitboard vulnerable;
  while (true) {
    _path.set(s);
    vulnerable = _getVulnerable(b, d);
    if (vulnerable[s]) {
      _hit = true;
      _where = s;
      break;
    }
    else {
      d = _getReflection(b, s, d);
    }
  }
}

/**
 * @brief Returns a bitboard representing pieces vulnerable by the laser fired
 * or reflected at a given direction.
 * @param b The board
 * @param d The laser's direction
 */
Bitboard Laser::_getVulnerable(const Board& b, Direction d) {
  //TODO consider making this a property of the board itself
  Bitboard vuln = b.getPiece(PHARAOH);
  // Handle direction blocked by anubis
  Direction anubis = static_cast<Direction>((2 + d) % 4);
  vuln |= b.getPiece(ANUBIS) & ~b.getDirection(anubis);
  // Handle direction where pyramid is vulnerable
  Direction pyramid = static_cast<Direction>((1 + d) % 4);
  vuln |= b.getPiece(PYRAMID) & b.getDirection(d) & b.getDirection(pyramid);
  return vuln;
}

/**
 * @brief Return the direction for a reflected laser given a board square.
 * @param b The board
 * @param s The square of the reflecting piece
 * @param d The laser's direction
 * @details It is assumed that vulnerable pieces have already been found and
 * taken care of. This is important because pyramid reflections are only valid
 * given the pyramid hasn't been eliminated.
 */
Direction Laser::_getReflection(const Board& b, Square s, Direction d) {
  //TODO you wrote this drunk, maybe have a look-see ;)
  Direction r = d;
  Piece p = b.getPieceAt(s);
  if (p == SCARAB || p == PYRAMID) {
    r = REFLECTS[b.getDirectionAt(s)][d];
  }
  return r;
}

/*
    // handle reflection
    // TODO replace ops with bit shifts
    else if (d == NORTH && !RANK_8[s]) {
      s = static_cast<Square>(s + NFILES);
    }
    else if (d == EAST && !FILE_J[s]) {
      s = static_cast<Square>(s + 1);
    }
    else if (d == SOUTH && !RANK_1[s]) {
      s = static_cast<Square>(s - NFILES);
    }
    else if (d == WEST && !FILE_A[s]) {
      s = static_cast<Square>(s - 1);
    }
    else {
      break;
    }
*/

} // namespace khet
