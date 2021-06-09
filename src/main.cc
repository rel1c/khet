#include "gamestate.h"
#include <iostream>

using namespace khet;

int main(int argc, const char **argv) {
  Gamestate g;
  size_t s = sizeof(g.squares_red);
  std::cout << s << std::endl;
  return 0;
}
