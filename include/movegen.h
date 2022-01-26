#include "board.h"

#ifndef MOVEGEN_H_
#define MOVEGEN_H_

// 1 sphinx rotation + 14 pieces * (8 moves + 2 rotations)
const int MAX_MOVES = 141;

extern const std::array<std::vector<Square>, NUM_SQUARES> MOVE_LIST;
extern const std::array<Bitboard, NUM_SQUARES> MOVE_BB;

using Moves = std::vector<Move>;

void gen(const Board&, Moves&);

#endif
