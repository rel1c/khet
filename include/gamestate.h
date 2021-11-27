#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "board.h"

namespace khet {

class Gamestate {
public:
  Gamestate(Layout);
private:
  Board board_;
  Color player_;
};

} // namespace khet

#endif
