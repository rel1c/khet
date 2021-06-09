/**
 * @file gamestate.h
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

namespace khet {

/**
 * @struct Gamestate
 * @brief A record of a game state for Khet.
 * @details This struct embodies a complete game state for the game of Khet.
 */
struct Gamestate {
  unsigned __int128 squares_red;
  unsigned __int128 squares_silver;
  unsigned __int128 pieces_red;
  unsigned __int128 pieces_silver;
  unsigned __int128 pieces_anubis;
  unsigned __int128 pieces_pharaoh;
  unsigned __int128 pieces_pyramid;
  unsigned __int128 pieces_scarab;
  unsigned __int128 pieces_sphinx;
  unsigned __int128 orients_n;
  unsigned __int128 orients_e;
  unsigned __int128 orients_s;
  unsigned __int128 orients_w;
  unsigned int turn;
  bool silver_to_play;
};

} // namespace khet

#endif
