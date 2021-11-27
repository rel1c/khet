#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
  board_ = Board(layout);
  player_ = SILVER;
}

} // namespace khet
