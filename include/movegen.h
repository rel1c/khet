#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "board.h"
#include "move.h"

class Move; // forward declaration

namespace khet {

using Moves = std::vector<Move>;

class MoveGen {
public:
  MoveGen();
  MoveGen(const Board&);
  Moves getMoves() const;
  void setBoard(const Board&);
private:
  static const int NMOVES = 121;
  static const std::array<SquareVec, NSQUARES> _lookup_sqrs;
  static const std::array<Bitboard, NSQUARES> _lookup_moves;
  static const std::array<Rotation, 4> _sphinxRotations;

  Moves _moves;

  void _genMoves(const Board&);
  void _genSwaps(const Board&, Square);
  void _genSphinxRotation(const Board&, Square);
  void _isLegal(const Move&) const;
};

} // namespace khet

#endif
