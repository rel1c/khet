/**
 * @file gamestate.cc
 */

#include "gamestate.h"

namespace khet {

  const Bitboard Gamestate::squares_red = Bitboard(
    "0100000001"
    "0000000001"
    "0000000001"
    "0000000001"
    "0000000001"
    "0000000001"
    "0000000001"
    "0100000001"
  );
  const Bitboard Gamestate::squares_silver = Bitboard(
    "1000000010"
    "1000000000"
    "1000000000"
    "1000000000"
    "1000000000"
    "1000000000"
    "1000000000"
    "1000000010"
  );

  Bitboard Gamestate::AllPieces() {
    return pieces_red | pieces_silver;
  }

  Bitboard Gamestate::RedAnubis() {
    return pieces_red & pieces_anubis;
  }

  Bitboard Gamestate::RedPharaoh() {
    return pieces_red & pieces_pharaoh;
  }

  Bitboard Gamestate::RedPyramid() {
    return pieces_red & pieces_pyramid;
  }

  Bitboard Gamestate::RedScarab() {
    return pieces_red & pieces_scarab;
  }

  Bitboard Gamestate::RedSphinx() {
    return pieces_red & pieces_sphinx; 
  }

  Bitboard Gamestate::RedSquares() {
    return squares_red;
  }

  Bitboard Gamestate::SilverAnubis() {
    return pieces_silver & pieces_anubis;
  }

  Bitboard Gamestate::SilverPharaoh() {
    return pieces_silver & pieces_pharaoh;
  }

  Bitboard Gamestate::SilverPyramid() {
    return pieces_silver & pieces_pyramid;
  }

  Bitboard Gamestate::SilverScarab() {
    return pieces_silver & pieces_scarab;
  }

  Bitboard Gamestate::SilverSphinx() {
    return pieces_silver & pieces_sphinx; 
  }

  Bitboard Gamestate::SilverSquares() {
    return squares_silver;
  }

} // namespace khet
