#ifndef LASER_H_
#define LASER_H_

#include "move.h"

namespace khet {

enum BitPosition {
  LSB,
  MSB
}

using ReflectTable = std::array<std::array<Bitboard, NDIRECTIONS>, NSQUARES>;
using OrderTable = std::array<BitPosition, NDIRECTIONS>;

class Laser {
public:
  Bitboard fire(const Board&);
  void showReflectTable() const;
private:
  static const ReflectTable _reflections;
  static const OrderTable _reflectOrder;
};

} // namespace khet

#endif

/*TODO:
 * 2d look-up array [square][direction] that has a laser
 * path stored as a bitboard. depending on the direction,
 * take either the highest or lowest bit from a bitboard
 * to determine the square that has been hit.
 *
 * north: lowest
 * east: lowest
 * south: highest
 * west: highest
 *
 * might be good to store in the board pre-computed values for
 * eliminated by direction boards, so another 2d array as a
 * member variable. [direction-of-laser][to-be-eliminated]
 *
 * the entire engine might be sped up by constructing boards in
 * this fashion, that is, computing them after every move/turn.
 *
 * red_anubis_north might be faster than looking up the color
 * then the piece and then the direction. this requires more
 * thought.
 */
