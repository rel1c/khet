#include "gamestate.h"
#include "game.h"

#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Bitboard b;
  Gamestate gs;
  Game g;
  std::cout << "Bitboard size: " << sizeof(b) << std::endl;
  std::cout << "Gamestate size: " << sizeof(gs) << std::endl;
  std::cout << "Full bitboard test: " << std::endl;
  Bitlogic::Display(Bitlogic::board_full);
  std::cout << "Red squares gamestate test: " << std::endl;
  Bitlogic::Display(gs.RedSquares());
  Bitlogic::Display(g.GetTranslation(6));
  return 0;
}
