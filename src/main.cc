#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "movegen.h"

unsigned long long perft(const Board& board, int depth) {
  if (depth == 0)
    return 1;
  unsigned long long nodes = 0;
  Moves moves;
  moves.reserve(MAX_MOVES);
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

void listPieceBits() {
  std::map<std::string, Piece> piece_bits = {
    {"SILVER_ANUBIS_NORTH", SILVER_ANUBIS_NORTH},
    {"SILVER_ANUBIS_EAST", SILVER_ANUBIS_EAST},
    {"SILVER_ANUBIS_SOUTH", SILVER_ANUBIS_SOUTH},
    {"SILVER_ANUBIS_WEST", SILVER_ANUBIS_WEST},
    {"SILVER_EYE_OF_HORUS_NORTH", SILVER_EYE_OF_HORUS_NORTH},
    {"SILVER_EYE_OF_HORUS_EAST", SILVER_EYE_OF_HORUS_EAST},
    {"SILVER_EYE_OF_HORUS_SOUTH", SILVER_EYE_OF_HORUS_SOUTH},
    {"SILVER_EYE_OF_HORUS_WEST", SILVER_EYE_OF_HORUS_WEST},
    {"SILVER_PHARAOH_NORTH", SILVER_PHARAOH_NORTH},
    {"SILVER_PHARAOH_EAST", SILVER_PHARAOH_EAST},
    {"SILVER_PHARAOH_SOUTH", SILVER_PHARAOH_SOUTH},
    {"SILVER_PHARAOH_WEST", SILVER_PHARAOH_WEST},
    {"SILVER_PYRAMID_NORTH", SILVER_PYRAMID_NORTH},
    {"SILVER_PYRAMID_EAST", SILVER_PYRAMID_EAST},
    {"SILVER_PYRAMID_SOUTH", SILVER_PYRAMID_SOUTH},
    {"SILVER_PYRAMID_WEST", SILVER_PYRAMID_WEST},
    {"SILVER_SCARAB_NORTH", SILVER_SCARAB_NORTH},
    {"SILVER_SCARAB_EAST", SILVER_SCARAB_EAST},
    {"SILVER_SCARAB_SOUTH", SILVER_SCARAB_SOUTH},
    {"SILVER_SCARAB_WEST", SILVER_SCARAB_WEST},
    {"SILVER_SPHINX_NORTH", SILVER_SPHINX_NORTH},
    {"SILVER_SPHINX_EAST", SILVER_SPHINX_EAST},
    {"SILVER_SPHINX_SOUTH", SILVER_SPHINX_SOUTH},
    {"SILVER_SPHINX_WEST", SILVER_SPHINX_WEST},
    {"RED_ANUBIS_NORTH", RED_ANUBIS_NORTH},
    {"RED_ANUBIS_EAST", RED_ANUBIS_EAST},
    {"RED_ANUBIS_SOUTH", RED_ANUBIS_SOUTH},
    {"RED_ANUBIS_WEST", RED_ANUBIS_WEST},
    {"RED_EYE_OF_HORUS_NORTH", RED_EYE_OF_HORUS_NORTH},
    {"RED_EYE_OF_HORUS_EAST", RED_EYE_OF_HORUS_EAST},
    {"RED_EYE_OF_HORUS_SOUTH", RED_EYE_OF_HORUS_SOUTH},
    {"RED_EYE_OF_HORUS_WEST", RED_EYE_OF_HORUS_WEST},
    {"RED_PHARAOH_NORTH", RED_PHARAOH_NORTH},
    {"RED_PHARAOH_EAST", RED_PHARAOH_EAST},
    {"RED_PHARAOH_SOUTH", RED_PHARAOH_SOUTH},
    {"RED_PHARAOH_WEST", RED_PHARAOH_WEST},
    {"RED_PYRAMID_NORTH", RED_PYRAMID_NORTH},
    {"RED_PYRAMID_EAST", RED_PYRAMID_EAST},
    {"RED_PYRAMID_SOUTH", RED_PYRAMID_SOUTH},
    {"RED_PYRAMID_WEST", RED_PYRAMID_WEST},
    {"RED_SCARAB_NORTH", RED_SCARAB_NORTH},
    {"RED_SCARAB_EAST", RED_SCARAB_EAST},
    {"RED_SCARAB_SOUTH", RED_SCARAB_SOUTH},
    {"RED_SCARAB_WEST", RED_SCARAB_WEST},
    {"RED_SPHINX_NORTH", RED_SPHINX_NORTH},
    {"RED_SPHINX_EAST", RED_SPHINX_EAST},
    {"RED_SPHINX_SOUTH", RED_SPHINX_SOUTH},
    {"RED_SPHINX_WEST", RED_SPHINX_WEST}
  };
  for (const auto& pair : piece_bits) {
    std::cout << std::setw(25) << pair.first << ": " << std::bitset<8>(pair.second) << std::endl;
  }
}

int main(int argc, const char **argv) {
  listPieceBits();
  Board b;
  b.setPkn(
      "2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1p1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0"
  );

  int depth = 3;
  if (argc == 2)
    depth = std::atoi(argv[1]);
  unsigned long long n = perft(b, depth);
  std::cout << "perft at depth " << depth << " : " << n << " nodes" << std::endl;
}
