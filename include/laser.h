#include <array>
#include "board.h"

#ifndef LASER_H_
#define LASER_H_

class Laser {
public:
  Laser() = default;

  const Capture fire(const Board&, Square, Direction);
  bool escaping(Square s, Direction d) const;

private:
  std::array<Bitboard, NUM_COLORS> _path_bb = {};
  std::array<std::vector<Square>, NUM_COLORS> _path = {};
  
  Direction _reflect(Direction, Piece) const {
    
  }
};

inline bool Laser::escaping(Square s, Direction d) const {
  //unsigned int i = static_cast<unsigned int> s;
  return (s < 10 && d == SOUTH) ||
         (s >= 70 && d == NORTH) ||
         (s % 10 == 0 && d == WEST) ||
         (s % 10 == 9 && d == EAST);
}

#endif
