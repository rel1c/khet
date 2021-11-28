#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
  board_ = Board(layout);
  player_ = SILVER;
}

void Gamestate::GenerateMoves() {
  GenerateAnubisMoves();
  GeneratePharaohMoves();
  GeneratePyramidMoves();
  GenerateScarabMoves();
  GenerateSphinxMoves();
}

void Gamestate::GenerateAnubisMoves() {}
void Gamestate::GeneratePharaohMoves() {}
void Gamestate::GeneratePyramidMoves() {}
void Gamestate::GenerateScarabMoves() {}
void Gamestate::GenerateSphinxMoves() {}

} // namespace khet
