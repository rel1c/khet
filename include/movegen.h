#include "board.h"

#ifndef MOVEGEN_H_
#define MOVEGEN_H_

// 1 sphinx rotation + 14 pieces * (8 moves + 2 rotations)
const int MAX_MOVES = 141;

extern const std::array<Bitboard, NUM_SQUARES> init_move_bb();
extern const std::array<std::vector<Square>, NUM_SQUARES> init_move_list();

extern const std::array<Bitboard, NUM_SQUARES> MOVE_BB;
extern const std::array<std::vector<Square>, NUM_SQUARES> MOVE_LIST;

using Moves = std::vector<Move>;
void gen(const Board&, Moves&);

#endif

/*
 * TODO
 *
 * movegen parameterized tests
 *
 * move lists for depth 1 for all game boards?
 * possibly overkill...
 *
 * where are the calls to swap piece?!
 *
 * why not just restore the previous state instead of undoing a move?
 *    if state, then restore, else undo move
 *
 * at my wits end how else to speed up move generation, outside of look-ups
 *
 * the last might speed things up by eliminating pieces
 * i'm curious just how many states in the current tree are repeats
 * i'm assuming tons
 * ----------------------------------
 *
 *  1. use look-up table for move lists, per type move/swap
 *  2. use piece list so as not to iterate all 80 squares
 *
 *  [1,0,0,0,0]
 *  [0,1,0,0,0]
 *  ....
 *  [0,0,0,0,1]
 *
 *  [1,1,0,0,0]
 *  [0,1,1,0,0]
 *  ....
 *  [0,0,0,1,1]
 *
 *  [1,0,0,0,0] -> [1,1,0,0,0] [1,0,1,0,0]
 *
 *  1. generate the 56 possible configurations of a 3x3 bitgrid
 *  2. shift and store each configuration for each square
 *     > the key is the resulting bitboard and the value a list of squares
 */
