#ifndef LASER_H_
#define LASER_H_

#include "move.h"

namespace khet {

const Square SILVER_LASER = J1;
const Square RED_LASER = A8;

class Laser {
public:
  Laser();
  Laser(const Board&);

  bool didHit();
  Bitboard getPath();
  Square getWhere();

  void fire(const Board&);
private:
  //std::vector<Square> _path;
  bool _hit;
  Bitboard _path;
  Square _where;

  Bitboard _getVulnerable(const Board&, Direction);
  Direction _getReflection(const Board&, Direction);
};

} // namespace khet

#endif
