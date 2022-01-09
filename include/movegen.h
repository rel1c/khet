#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "move.h"

namespace khet {

using Moves = std::vector<Move>;

class MoveGen {
public:
  MoveGen();
  MoveGen(const Board&);
  Moves getMoves() const;
  void gen(const Board&);
private:
  // 1 sphinx rotation + 12 pieces * 8 moves + 2 rotations
  static const int MAX_MOVES = 121;
  static const std::array<SquareVec, NSQUARES> _lookup_sqrs;
  static const std::array<Bitboard, NSQUARES> _lookup_moves;
  static const std::array<Rotation, 4> _sphinxRotations;

  Moves _moves;

  void _genMoves(const Board&);
  void _genSwaps(const Board&, Square);
  void _genSphinxRotation(const Board&, Square);
};

} // namespace khet

#endif
