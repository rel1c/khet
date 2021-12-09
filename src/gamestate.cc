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
  int n_pieces = pieces.count();
  // iterate over them and generate possible actions
  for (int i = 0; i < NSQUARES; i++) {
    if (n_pieces <= 0)
      break;
    n_pieces--;
    Square s = static_cast<Square>(i);
    if (pieces[i] & board_.sphinx_[i]) { //TODO refactor to use less logic
      genSphinxActions(s);
      continue;
    }
    else if (pieces[i] & board_.scarab_[i]) {
      genSwaps(s);
    }
    genMoves(s);
    genRotations(s);
  }
}

void Gamestate::genMoves(Square s) {
  Bitboard able = board_.moves_[s] & ~(board_.red_ | board_.silver_);
  for (Square t : board_.moves_sqrs_[s]) {
    if (able[t]) {
      actions_.push_back(Action(s, t));
    }
  }
}

void Gamestate::genSwaps(Square s) {
  Bitboard able = board_.moves_[s] & (board_.pyramid_ | board_.anubis_);
  for (Square t : board_.moves_sqrs_[s]) {
    if (able[t]) {
      actions_.push_back(Action(s, t, true)); //TODO this is NOT clear
    }
  }
}

void Gamestate::genRotations(Square s) {
  Direction dir_old, dir_new;
  if (board_.north_[s])
    dir_old = NORTH;
  else if (board_.east_[s])
    dir_old = EAST;
  else if (board_.south_[s])
    dir_old = SOUTH;
  else if (board_.west_[s])
    dir_old = WEST;
  else
    return; //TODO need an error case (should never happen)
  dir_new = static_cast <Direction>((dir_old - 1) % 4);
  actions_.push_back(Action(s, dir_old, dir_new));
  dir_new = static_cast <Direction>((dir_old + 1) % 4);
  actions_.push_back(Action(s, dir_old, dir_new));
}

void Gamestate::genSphinxActions(Square s) {
  Direction dir_old, dir_new;
  if (board_.north_[s])
    dir_old = NORTH;
  else if (board_.east_[s])
    dir_old = EAST;
  else if (board_.south_[s])
    dir_old = SOUTH;
  else if (board_.west_[s])
    dir_old = WEST;
  else
    return; //TODO need an error case (should never happen)
  dir_new = static_cast <Direction>(~dir_old);
  actions_.push_back(Action(s, dir_old, dir_new));
}

} // namespace khet
