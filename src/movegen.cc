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
  Color player = b.player();
  for (int i = 0; i < NUM_SQUARES; i++) {
    Square s = static_cast<Square>(i);
    Piece p = b.pieceOn(s); //TODO optimize this check out, only read filled/cached squares
    if (!p || colorOf(p) != player) //TODO same here, each player can have a cache
      continue;
    Bitboard possible = MOVE_BB[s] & ~b.blocked();
    Bitboard swaps, able;
    Color c = colorOf(p);
    Direction d = directionOf(p);
    PieceType pt = typeOf(p);
    switch (pt) {
    case SPHINX:
      m.push_back(makeMove(s, flip(d)));
      //std::cout << s << toChar(pt) << toChar(d) << std::endl;
      break;
    case SCARAB:
    case EYE_OF_HORUS:
      swaps = possible & (b.pieces(ANUBIS) | b.pieces(PYRAMID));
      for (Square t : MOVE_LIST[s]) {
        if (swaps[t]) {
          //std::cout << s << toChar(pt) << toChar(d) << std::endl;
          m.push_back(makeMove(s, t, true));
        }
      }
      // fall through
    case PYRAMID:
    case ANUBIS:
    case PHARAOH:
      able = possible & ~b.pieces(ALL_PIECES);
      for (Square t : MOVE_LIST[s]) {
        if (able[t]) {
          //std::cout << s << toChar(pt) << toChar(d) << std::endl;
          m.push_back(makeMove(s, t));
        }
      }
      m.push_back(makeMove(s, POSITIVE));
      m.push_back(makeMove(s, NEGATIVE));
      break;
    }
  }
}
