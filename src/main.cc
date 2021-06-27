#include "gamestate.h"

#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Bitboard b;
  Gamestate g;
  std::cout << "Bitboard size: " << sizeof(b) << std::endl;
  std::cout << "Gamestate size: " << sizeof(g) << std::endl;
  std::cout << "Full bitboard test: " << std::endl;
  Bitlogic::Display(Bitlogic::board_full);
  std::cout << "Red squares gamestate test: " << std::endl;
  Bitlogic::Display(g.RedSquares());
  return 0;
}
