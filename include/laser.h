#include <array>

#include "move.h"

#ifndef LASER_H_
#define LASER_H_

class Board;

using Bitboard = std::bitset <NUM_SQUARES>;

class Laser {
public:
  Laser() = default;

  const Capture fire(const Board&, Square, Direction);

private:
  std::array<Bitboard, NUM_COLORS> _path_bb = {};
  std::array<std::vector<Square>, NUM_COLORS> _path = {};

  inline bool _escaping(Square s, Direction d) const {
    //unsigned int i = static_cast<unsigned int> s;
    return (s < 10 && d == SOUTH) ||
           (s >= 70 && d == NORTH) ||
           (s % 10 == 0 && d == WEST) ||
           (s % 10 == 9 && d == EAST);
  }
  
  inline Direction _reflect(Direction d, Piece p) const {
    assert(p & REFLECTOR_MASK);
    return Direction(p & 1 ? d ^ EAST : d ^ WEST);
  }

  inline bool _elimPyramid(Direction ld, Direction pd) const {
    return (ld == pd & WEST) || (ld == (pd + 1) & WEST);
  }

  inline Square _advance(Square s, Direction d) {
    unsigned int t = static_cast<unsigned int>(s);
    if (_escaping(s, d))
      goto escaped;
    //TODO could operator overload (s + d)
    //These casts are so bad U_U *shame*
    switch (d) {
    case NORTH:
      return Square(t += 10);
    case EAST:
      return Square(t += 1);
    case SOUTH:
      return Square(t -= 10);
    case WEST:
      return Square(t -= 1);
    }
    escaped:
      return SQ_NONE;
  }
};

#endif
