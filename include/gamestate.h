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
  enum Layout { CLASSIC, DYNASTY, IMHOTEP };

  // Default constructor
  Gamestate(Layout layout = CLASSIC) {
    switch (layout) {
      case CLASSIC:;
      case DYNASTY:;
      case IMHOTEP:;
    }
  }

  Bitboard AllPieces();
  Bitboard RedAnubis();
  Bitboard RedPharaoh();
  Bitboard RedPyramid();
  Bitboard RedScarab();
  Bitboard RedSphinx();
  Bitboard RedSquares();
  Bitboard SilverAnubis();
  Bitboard SilverPharaoh();
  Bitboard SilverPyramid();
  Bitboard SilverScarab();
  Bitboard SilverSphinx();
  Bitboard SilverSquares();

  void SetNextPlayer() { silver_to_play = !silver_to_play; }
  bool IsTurnRed() { return !silver_to_play; }
  bool IsTurnSilver() { return silver_to_play; }

private:
  static const Bitboard squares_red;
  static const Bitboard squares_silver;
  Bitboard pieces_sphinx;
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
