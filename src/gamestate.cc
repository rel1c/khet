/**
 * @file gamestate.cc
 */

#include "gamestate.h"

namespace khet {
  Bitboard Gamestate::allPieces() {
    return pieces_red.bits | pieces_silver.bits;
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
