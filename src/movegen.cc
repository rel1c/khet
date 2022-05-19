#include "movegen.h"
#include <iostream>

const std::array<Bitboard, NUM_SQUARES> init_move_bb() {
  auto arr = decltype(MOVE_BB){};
  // establish move block for square B2,
  // the lowest indexed full block of 9 squares
  const unsigned int b2_moves = 0b11100000001010000000111;
  for (int i = 0; i < NUM_SQUARES; i++) {
    // trim bits off if square is on edge(s)
    Bitboard moves = b2_moves;
    if (i % 10 == 0) // left edge (remember endianness!)
      moves &= 0b11000000001000000000110;
    if (i % 10 == 9) // right edge
      moves &= 0b01100000000010000000011;
    if (i < 10) // bottom edge
      moves &= 0b11100000001010000000000;
    if (i >= 70) // top edge
      moves &= 0b00000000001010000000111;
    // shift bits into proper board position
    if (i < SQ_B2)
      moves >>= (SQ_B2 - i);
    else
      moves <<= (i - SQ_B2);
    arr[i] = moves;
  }
  return arr;
}

const std::array<std::vector<Square>, NUM_SQUARES> init_move_list() {
  auto arr = decltype(MOVE_LIST){};
  for (int i = 0; i < NUM_SQUARES; i++) {
    arr[i] = vecFromBB(MOVE_BB[i]);
  }
  return arr;
}

const std::array<Bitboard, NUM_SQUARES> MOVE_BB = init_move_bb();
const std::array<std::vector<Square>, NUM_SQUARES> MOVE_LIST = init_move_list();

void gen(const Board& b, Moves& m) {
  const Color player = b.player();
  const Bitboard pieces = b.pieces(player);
  const Bitboard blocked = b.blocked();
  const Bitboard open = ~blocked & ~b.pieces(ALL_PIECES);
  const Bitboard swappable = ~blocked & (b.pieces(ANUBIS) | b.pieces(PYRAMID));
  const std::vector<Square> piece_list = vecFromBB(pieces);
  for (auto& s : piece_list) {
    const Piece p = b.pieceOn(s);
    const Direction d = directionOf(p);
    const PieceType pt = typeOf(p);
    const Bitboard able = MOVE_BB[s] & open;
    const Bitboard swaps = MOVE_BB[s] & swappable;
    switch (pt) {
    case SPHINX:
      m.push_back(makeMove(s, flip(d)));
      break;
    case SCARAB:
    case EYE_OF_HORUS:
      for (Square t : MOVE_LIST[s]) {
        if (swaps[t]) {
          m.push_back(makeMove(s, t, true));
        }
      }
      // fall through
    case PYRAMID:
    case ANUBIS:
    case PHARAOH:
      for (Square t : MOVE_LIST[s]) {
        if (able[t]) {
          m.push_back(makeMove(s, t));
        }
      }
      m.push_back(makeMove(s, POSITIVE));
      m.push_back(makeMove(s, NEGATIVE));
      break;
    }
  }
}
