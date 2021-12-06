#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "board.h"
#include "action.h"

namespace khet {

class Gamestate {
public:
  Gamestate(Layout);
  void GenActions();
  void GenMoves(Color);
  void GenSwaps();
  void GenRotations();
private:
  Board board_;
  Color player_;
  std::vector<Action> actions_; //TODO statically allocate max possible actions
};

} // namespace khet

#endif
