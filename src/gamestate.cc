#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
  initBoard(board_, layout);
  player_ = SILVER;
}

} // namespace khet
