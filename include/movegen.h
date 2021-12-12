#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "board.h"
#include "move.h"

typedef std::vector<Move> Moves;

namespace khet {

class MoveGen {
public:
  MoveGen();
  MoveGen(const Board &board);
  Moves getMoves() const;
  void setBoard(const Board &board);
private:
  static const int NMOVES = 121;
  Moves _moves;

  void _genActions(Color);
  void _genMoves(Square);
  void _genSwaps(Square);
  void _genRotations(Square);
  void _genSphinxActions(Square);
  void _isLegal(const Action&) const;
private:
  
};

} // namespace khet

#endif
