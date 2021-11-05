#ifndef BOARD_H_
#define BOARD_H_

namespace khet {

struct Board {
  static const Bitboard squares_red;
  static const Bitboard squares_silver;

  Bitboard red;
  Bitboard silver;
  Bitboard north;
  Bitboard east;
  Bitboard south;
  Bitboard west;

  Bitboard anubis;
  Bitboard pharaoh;
  Bitboard pyramid;
  Bitboard scarab;
  Bitboard sphinx;
};

} // namespace khet

#endif
