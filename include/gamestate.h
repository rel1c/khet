#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "board.h"
#include "action.h"

namespace khet {

/* There is a max of 8 possible moves and 2 rotations per square, minus 2 moves
 * at each edge, and minus 5 moves at each corner, of which 2 are occupied by a
 * Sphinx. This means there are 688 possible actions in total. However, there
 * are only 13 pieces per player, 1 of which is a Sphinx. Therefore, at worst
 * case there are 122 possible actions per player on any given turn.
 */
const int NACTIONS = 122;

class Gamestate {
public:
  Gamestate(Layout);
  void GenActions(Color);
  void GenMoves(Square);
  void GenSwaps(Square);
  void GenRotations(Square);
  void GenSphinxAction(Square);
private:
  Board board_;
  Color player_;
  std::vector<Action> actions_;
};

} // namespace khet

#endif
