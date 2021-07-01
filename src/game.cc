/**
 * @file game.cc
 */

#include "game.h"

namespace khet {

const std::vector<Bitboard> Game::translations = {
  //TODO KISS! This is way complicated. There's a simple binary pattern here...
  Bitlogic::CreateBoard(std::vector<std::string>{"b1", "a2", "b2"}),             // a1
  Bitlogic::CreateBoard(std::vector<std::string>{"a1", "c1", "a2", "b2", "c2"}), // b1
  Bitlogic::CreateBoard(std::vector<std::string>{"b1", "d1", "b2", "c2", "d2"}), // c1
  Bitlogic::CreateBoard(std::vector<std::string>{"c1", "e1", "c2", "d2", "e2"}), // d1
  Bitlogic::CreateBoard(std::vector<std::string>{"d1", "f1", "d2", "e2", "f2"}), // e1
  Bitlogic::CreateBoard(std::vector<std::string>{"e1", "g1", "e2", "f2", "g2"}), // f1
  Bitlogic::CreateBoard(std::vector<std::string>{"f1", "h1", "f2", "g2", "h2"}), // g1
  Bitlogic::CreateBoard(std::vector<std::string>{"g1", "i1", "g2", "h2", "i2"}), // h1
  Bitlogic::CreateBoard(std::vector<std::string>{"h1", "j1", "h2", "i2", "j2"}), // i1
  Bitlogic::CreateBoard(std::vector<std::string>{"i1", "i2", "j2"})              // j1
};

const Bitboard& Game::GetTranslation(unsigned int i) const {
  return translations[i];
}

} // namespace khet
