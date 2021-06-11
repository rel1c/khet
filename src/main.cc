#include "gamestate.h"

#include <iostream>

using namespace khet;

//int main(int argc, const char **argv) {
int main() {
  Gamestate g;
  std::cout << "Gamestate size: " << sizeof(g) << std::endl;
  //std::cout << Gamestate::squares_red;
  return 0;
}
