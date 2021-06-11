/**
 * @file gamestate.cc
 */

#include "gamestate.h"

namespace khet {

  const Bitboard Gamestate::squares_red = Bitboard(0);
  const Bitboard Gamestate::squares_silver = Bitboard(0);
  const Bitboard Gamestate::pieces_sphinx = Bitboard(0);

  Bitboard Gamestate::allPieces() {
    return pieces_red | pieces_silver;
  }

  Bitboard Gamestate::redAnubis() {
    return pieces_red | pieces_anubis;
  }

  Bitboard Gamestate::redPharaoh() {
    return pieces_red | pieces_pharaoh;
  }

  Bitboard Gamestate::redPyramid() {
    return pieces_red | pieces_pyramid;
  }

  Bitboard Gamestate::redScarab() {
    return pieces_red | pieces_scarab;
  }

  Bitboard Gamestate::silverAnubis() {
    return pieces_silver | pieces_anubis;
  }

  Bitboard Gamestate::silverPharaoh() {
    return pieces_silver | pieces_pharaoh;
  }

  Bitboard Gamestate::silverPyramid() {
    return pieces_silver | pieces_pyramid;
  }

  Bitboard Gamestate::silverScarab() {
    return pieces_silver | pieces_scarab;
  }

} // namespace khet
