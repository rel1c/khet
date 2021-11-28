#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "board.h"
#include "move.h"

namespace khet {

class Gamestate {
public:
  Gamestate(Layout);
  void GenerateMoves();
  void GenerateAnubisMoves();
  void GeneratePharaohMoves();
  void GeneratePyramidMoves();
  void GenerateScarabMoves();
  void GenerateSphinxMoves();
private:
  Board board_;
  Color player_;
  std::vector<Move> moves_; //TODO statically allocate max possible moves
};

} // namespace khet

#endif
