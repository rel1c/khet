/**
 * @file gamestate.h
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "bitboard.h"

namespace khet {

/**
 * @struct Gamestate
 * @brief A record of a game state for Khet.
 * @details This struct embodies a complete game state for the game of Khet.
 */
struct Gamestate {
  Bitboard squares_red;
  Bitboard squares_silver;
  Bitboard pieces_red;
  Bitboard pieces_silver;
  Bitboard pieces_anubis;
  Bitboard pieces_pharaoh;
  Bitboard pieces_pyramid;
  Bitboard pieces_scarab;
  Bitboard pieces_sphinx;
  Bitboard orients_n;
  Bitboard orients_e;
  Bitboard orients_s;
  Bitboard orients_w;
  unsigned int turn;
  bool silver_to_play;
};

} // namespace khet

#endif
