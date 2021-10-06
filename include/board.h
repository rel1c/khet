#ifndef BOARD_H_
#define BOARD_H_

namespace khet {

struct Board {
  static const bitboard squares_red;
  static const bitboard squares_silver;

  bitboard red;
  bitboard silver;
  bitboard north;
  bitboard east;
  bitboard south;
  bitboard west;

  bitboard anubis;
  bitboard pharaoh;
  bitboard pyramid;
  bitboard scarab;
  bitboard sphinx;
};

} // namespace khet

#endif
