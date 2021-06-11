#include "gamestate.h"

#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Bitboard b;
  Gamestate g;
  std::cout << "Bitboard size: " << sizeof(b) << std::endl;
  std::cout << "Gamestate size: " << sizeof(g) << std::endl;
  Bitlogic::display(Bitlogic::boardFull);

  uint8_t byteboard[80];
  std::cout << "Byteboard size: " << sizeof(byteboard) << std::endl;



  return 0;
}
