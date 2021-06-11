/**
 * @file gamestate.cc
 */

#include "gamestate.h"

namespace khet {

  const Bitboard Gamestate::squares_red = Bitboard(0);
  const Bitboard Gamestate::squares_silver = Bitboard(0);
  const Bitboard Gamestate::pieces_sphinx = Bitboard(0);

  Bitboard Gamestate::AllPieces() {
    return pieces_red | pieces_silver;
  }

  Bitboard Gamestate::RedAnubis() {
    return pieces_red | pieces_anubis;
  }

  Bitboard Gamestate::RedPharaoh() {
    return pieces_red | pieces_pharaoh;
  }

  Bitboard Gamestate::RedPyramid() {
    return pieces_red | pieces_pyramid;
  }

  Bitboard Gamestate::RedScarab() {
    return pieces_red | pieces_scarab;
  }

  Bitboard Gamestate::SilverAnubis() {
    return pieces_silver | pieces_anubis;
  }

  Bitboard Gamestate::SilverPharaoh() {
    return pieces_silver | pieces_pharaoh;
  }

  Bitboard Gamestate::SilverPyramid() {
    return pieces_silver | pieces_pyramid;
  }

  Bitboard Gamestate::SilverScarab() {
    return pieces_silver | pieces_scarab;
  }

} // namespace khet
