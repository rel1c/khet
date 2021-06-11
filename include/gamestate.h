/**
 * @file gamestate.h
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "bitboard.h"

namespace khet {

/**
 * @class Gamestate
 * @brief A record of a game state for Khet.
 * @details This class embodies a complete game state for the game of Khet.
 */
class Gamestate {
public:
  enum Configuration { CLASSIC, DYNASTY, IMHOTEP };
  static unsigned int turn;
  static const Bitboard squares_red;
  static const Bitboard squares_silver;
  static const Bitboard pieces_sphinx;

  Bitboard allPieces();
  Bitboard redAnubis();
  Bitboard redPharaoh();
  Bitboard redPyramid();
  Bitboard redScarab();
  Bitboard silverAnubis();
  Bitboard silverPharaoh();
  Bitboard silverPyramid();
  Bitboard silverScarab();

  void incrementTurn() { turn++; }
  void setNextPlayer() { silver_to_play = !silver_to_play; }
  bool isTurnRed() { return !silver_to_play; }
  bool isTurnSilver() { return silver_to_play; }

private:
  Bitboard pieces_red;
  Bitboard pieces_silver;
  Bitboard pieces_anubis;
  Bitboard pieces_pharaoh;
  Bitboard pieces_pyramid;
  Bitboard pieces_scarab;
  Bitboard orients_n;
  Bitboard orients_e;
  Bitboard orients_s;
  Bitboard orients_w;
  bool silver_to_play;
};

} // namespace khet

#endif
