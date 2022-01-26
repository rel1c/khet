#include <iostream>
#include <map>
#include <string>
#include "movegen.h"

static void show(Board&);

int main(int argc, const char **argv) {
  Board b;
  b.setPkn(
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0"
  );
  Moves m;
  gen(b, m);
  std::cout << "number of moves: " << m.size() << std::endl;
}
