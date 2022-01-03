#include <iostream>
#include "movegen.h"
#include "laser.h"

using namespace khet;

unsigned long long perft(const Board& board, int depth) {
  if (depth == 0)
    return 1;
  unsigned long long nodes = 0;
  MoveGen mg(board);
  Moves moves = mg.getMoves();
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
  displayBitboard(FILE_A);
  Laser l;
  l.showReflectTable();
  return 0;
}
