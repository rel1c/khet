#include <iostream>
#include <map>
#include <string>
#include "movegen.h"

unsigned long long perft(const Board& board, int depth) {
  if (depth == 0)
    return 1;
  unsigned long long nodes = 0;
  Moves moves;
  gen(board, moves);
  Board moved_board = board;
  //std::cout << "number of moves: " << moves.size() << std::endl;
  for (auto move : moves) {
    //std::cout << move.toStr() << std::endl;
    moved_board.doMove(move);
    nodes += perft(board, depth - 1);
    moved_board.undoMove(move);
  }
  return nodes;
}

int main(int argc, const char **argv) {
  Board b;
  b.setPkn(
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0"
  );

  int d = 1;
  if (argc == 2)
    d = std::atoi(argv[1]);
  unsigned long long n = perft(b, d);
  std::cout << "perft at depth " << d << " : " << n << " nodes" << std::endl;
}
