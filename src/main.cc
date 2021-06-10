#include "gamestate.h"
#include "bitboard.h" //
#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Gamestate g;
  std::cout << "Gamestate size: " << sizeof(g) << std::endl;
  return 0;
}
