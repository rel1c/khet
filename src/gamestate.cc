#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
  board_ = Board(layout);
  player_ = SILVER;
}

/**
 * @brief
 * @param turn
 */
void Gamestate::GenMoves(Color turn) {
  Bitboard vacant = ~(board_.silver_ & board_.red_);
  Bitboard pieces = ~board_.sphinx_;
  if (turn == RED)
    pieces &= board_.red_;
  else
    pieces &= board_.silver_;
  int n_pieces = pieces.count();
  for (int i = 0; i < NSQUARES; i++) {
    if (n_pieces <= 0)
      break;
    Bitboard moves = board_.moves_[i] & vacant;
    if (moves.any()) {
      int n_moves = moves.count();
      for (int j = 0; j < NSQUARES; j++) { //TODO replace with square look-up?
        if (n_moves <= 0)
          break;
        if (moves[i]) {
          Action act;
          act.from_ = static_cast <Square>(i);
          act.to_ = static_cast <Square>(j);
          actions_.push_back(act);
        }
      }
    }
  }
}

void Gamestate::GenerateSwaps() {}
void Gamestate::GenerateRotations() {}

} // namespace khet
