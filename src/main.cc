#include "gamestate.h"

#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Bitboard b;
  Gamestate g;
  std::cout << "Bitboard size: " << sizeof(b) << std::endl;
  std::cout << "Gamestate size: " << sizeof(g) << std::endl;
  Bitlogic::Display(Bitlogic::board_full);
  return 0;
}
