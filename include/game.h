/**
 * @file game.h
 */

#ifndef GAME_H_
#define GAME_H_

#include "bitboard.h"

namespace khet {

class Game {
public:
  const Bitboard& GetTranslation(unsigned int i) const;
private:
  static const std::vector<Bitboard> translations;
};

} // namespace khet

#endif
