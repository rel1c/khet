#include "gamestate.h"

namespace khet {

Gamestate::Gamestate() {
  board_ = Board(CLASSIC);
  player_ = SILVER;
  actions_.reserve(NACTIONS);
}

Gamestate::Gamestate(Layout layout=CLASSIC) {
  board_ = Board(layout);
  player_ = SILVER;
  actions_.reserve(NACTIONS);
}

std::vector<Action>& Gamestate::getActions() {
  return actions_;
}

Board& Gamestate::getBoard() {
  return board_;
}

/**
 * @brief
 * @param turn
 */
void Gamestate::genActions(Color turn) {
  actions_.clear();
  // copy in pieces for current turn
  Bitboard pieces;
  if (turn == RED)
    pieces = board_.red_;
  else
    pieces = board_.silver_;
  Bitboard vacant = ~(board_.red_ | board_.silver_);
  int n_pieces = pieces.count();
  // iterate over them and generate possible actions
  for (int i = 0; i < NSQUARES; i++) {
    if (n_pieces <= 0)
      break;
    n_pieces--;
    Square s = static_cast<Square>(i);
    if (pieces[i] & board_.sphinx_[i]) { //TODO refactor to use less logic
      genSphinxAction(s);
      continue;
    }
    else if (pieces[i] & board_.scarab_[i]) {
      genSwaps(s);
    }
    genMoves(s, vacant);
    genRotations(s);
  }
}

void Gamestate::genMoves(Square s, Bitboard& bb) {
  Bitboard possible_moves = board_.moves_[s] & bb;
  for (Square t : board_.moves_sqrs_[s]) {
    if (possible_moves[t]) {
      actions_.push_back(Action(s,t));
    }
  }
}

void Gamestate::genSwaps(Square s) {}
void Gamestate::genRotations(Square s) {}
void Gamestate::genSphinxAction(Square s) {}

} // namespace khet
