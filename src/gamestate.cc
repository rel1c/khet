#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
  board_ = Board(layout);
  player_ = SILVER;
  actions_.reserve(NACTIONS);
}

void Gamestate::GenActions(Color turn) {
  actions_.clear();
  // copy in this turn's pieces
  Bitboard pieces;
  if (turn == RED)
    pieces = board_.red_;
  else
    pieces = board_.silver_;
  int n_pieces = pieces.count();
  // iterate over them
  for (int i = 0; i < NSQUARES; i++) {
    Square s = static_cast<Square>(i);
    if (n_pieces <= 0)
      break;
    if (pieces[i] & board_.sphinx_[i]) { //TODO refactor to use less logic
      GenSphinxAction(s);
      continue;
    }
    else if (pieces[i] & board_.scarab_[i]) {
      GenSwaps(s);
    }
    GenMoves(s);
    GenRotations(s);
  }
}

/**
 * @brief
 * @param turn
 */
/*
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
*/

void Gamestate::GenMoves(Square s) {}
void Gamestate::GenSwaps(Square s) {}
void Gamestate::GenRotations(Square s) {}
void Gamestate::GenSphinxAction(Square s) {}

} // namespace khet
