#include "movegen.h"
#include <iostream>

//TODO calculate this at compile time with a loop
const std::array<std::vector<Square>, NUM_SQUARES> MOVE_LIST = {
  std::vector<Square> {SQ_B1, SQ_A2, SQ_B2},
  std::vector<Square> {SQ_A1, SQ_C1, SQ_A2, SQ_B2, SQ_C2},
  std::vector<Square> {SQ_B1, SQ_D1, SQ_B2, SQ_C2, SQ_D2},
  std::vector<Square> {SQ_C1, SQ_E1, SQ_C2, SQ_D2, SQ_E2},
  std::vector<Square> {SQ_D1, SQ_F1, SQ_D2, SQ_E2, SQ_F2},
  std::vector<Square> {SQ_E1, SQ_G1, SQ_E2, SQ_F2, SQ_G2},
  std::vector<Square> {SQ_F1, SQ_H1, SQ_F2, SQ_G2, SQ_H2},
  std::vector<Square> {SQ_G1, SQ_I1, SQ_G2, SQ_H2, SQ_I2},
  std::vector<Square> {SQ_H1, SQ_J1, SQ_H2, SQ_I2, SQ_J2},
  std::vector<Square> {SQ_I1, SQ_I2, SQ_J2},

  std::vector<Square> {SQ_A1, SQ_B1, SQ_B2, SQ_A3, SQ_B3},
  std::vector<Square> {SQ_A1, SQ_B1, SQ_C1, SQ_A2, SQ_C2, SQ_A3, SQ_B3, SQ_C3},
  std::vector<Square> {SQ_B1, SQ_C1, SQ_D1, SQ_B2, SQ_D2, SQ_B3, SQ_C3, SQ_D3},
  std::vector<Square> {SQ_C1, SQ_D1, SQ_E1, SQ_C2, SQ_E2, SQ_C3, SQ_D3, SQ_E3},
  std::vector<Square> {SQ_D1, SQ_E1, SQ_F1, SQ_D2, SQ_F2, SQ_D3, SQ_E3, SQ_F3},
  std::vector<Square> {SQ_E1, SQ_F1, SQ_G1, SQ_E2, SQ_G2, SQ_E3, SQ_F3, SQ_G3},
  std::vector<Square> {SQ_F1, SQ_G1, SQ_H1, SQ_F2, SQ_H2, SQ_F3, SQ_G3, SQ_H3},
  std::vector<Square> {SQ_G1, SQ_H1, SQ_I1, SQ_G2, SQ_I2, SQ_G3, SQ_H3, SQ_I3},
  std::vector<Square> {SQ_H1, SQ_I1, SQ_J1, SQ_H2, SQ_J2, SQ_H3, SQ_I3, SQ_J3},
  std::vector<Square> {SQ_I1, SQ_J1, SQ_I2, SQ_I3, SQ_J3},

  std::vector<Square> {SQ_A2, SQ_B2, SQ_B3, SQ_A4, SQ_B4},
  std::vector<Square> {SQ_A2, SQ_B2, SQ_C2, SQ_A3, SQ_C3, SQ_A4, SQ_B4, SQ_C4},
  std::vector<Square> {SQ_B2, SQ_C2, SQ_D2, SQ_B3, SQ_D3, SQ_B4, SQ_C4, SQ_D4},
  std::vector<Square> {SQ_C2, SQ_D2, SQ_E2, SQ_C3, SQ_E3, SQ_C4, SQ_D4, SQ_E4},
  std::vector<Square> {SQ_D2, SQ_E2, SQ_F2, SQ_D3, SQ_F3, SQ_D4, SQ_E4, SQ_F4},
  std::vector<Square> {SQ_E2, SQ_F2, SQ_G2, SQ_E3, SQ_G3, SQ_E4, SQ_F4, SQ_G4},
  std::vector<Square> {SQ_F2, SQ_G2, SQ_H2, SQ_F3, SQ_H3, SQ_F4, SQ_G4, SQ_H4},
  std::vector<Square> {SQ_G2, SQ_H2, SQ_I2, SQ_G3, SQ_I3, SQ_G4, SQ_H4, SQ_I4},
  std::vector<Square> {SQ_H2, SQ_I2, SQ_J2, SQ_H3, SQ_J3, SQ_H4, SQ_I4, SQ_J4},
  std::vector<Square> {SQ_I2, SQ_J2, SQ_I3, SQ_I4, SQ_J4},

  std::vector<Square> {SQ_A3, SQ_B3, SQ_B4, SQ_A5, SQ_B5},
  std::vector<Square> {SQ_A3, SQ_B3, SQ_C3, SQ_A4, SQ_C4, SQ_A5, SQ_B5, SQ_C5},
  std::vector<Square> {SQ_B3, SQ_C3, SQ_D3, SQ_B4, SQ_D4, SQ_B5, SQ_C5, SQ_D5},
  std::vector<Square> {SQ_C3, SQ_D3, SQ_E3, SQ_C4, SQ_E4, SQ_C5, SQ_D5, SQ_E5},
  std::vector<Square> {SQ_D3, SQ_E3, SQ_F3, SQ_D4, SQ_F4, SQ_D5, SQ_E5, SQ_F5},
  std::vector<Square> {SQ_E3, SQ_F3, SQ_G3, SQ_E4, SQ_G4, SQ_E5, SQ_F5, SQ_G5},
  std::vector<Square> {SQ_F3, SQ_G3, SQ_H3, SQ_F4, SQ_H4, SQ_F5, SQ_G5, SQ_H5},
  std::vector<Square> {SQ_G3, SQ_H3, SQ_I3, SQ_G4, SQ_I4, SQ_G5, SQ_H5, SQ_I5},
  std::vector<Square> {SQ_H3, SQ_I3, SQ_J3, SQ_H4, SQ_J4, SQ_H5, SQ_I5, SQ_J5},
  std::vector<Square> {SQ_I3, SQ_J3, SQ_I4, SQ_I5, SQ_J5},

  std::vector<Square> {SQ_A4, SQ_B4, SQ_B5, SQ_A6, SQ_B6},
  std::vector<Square> {SQ_A4, SQ_B4, SQ_C4, SQ_A5, SQ_C5, SQ_A6, SQ_B6, SQ_C6},
  std::vector<Square> {SQ_B4, SQ_C4, SQ_D4, SQ_B5, SQ_D5, SQ_B6, SQ_C6, SQ_D6},
  std::vector<Square> {SQ_C4, SQ_D4, SQ_E4, SQ_C5, SQ_E5, SQ_C6, SQ_D6, SQ_E6},
  std::vector<Square> {SQ_D4, SQ_E4, SQ_F4, SQ_D5, SQ_F5, SQ_D6, SQ_E6, SQ_F6},
  std::vector<Square> {SQ_E4, SQ_F4, SQ_G4, SQ_E5, SQ_G5, SQ_E6, SQ_F6, SQ_G6},
  std::vector<Square> {SQ_F4, SQ_G4, SQ_H4, SQ_F5, SQ_H5, SQ_F6, SQ_G6, SQ_H6},
  std::vector<Square> {SQ_G4, SQ_H4, SQ_I4, SQ_G5, SQ_I5, SQ_G6, SQ_H6, SQ_I6},
  std::vector<Square> {SQ_H4, SQ_I4, SQ_J4, SQ_H5, SQ_J5, SQ_H6, SQ_I6, SQ_J6},
  std::vector<Square> {SQ_I4, SQ_J4, SQ_I5, SQ_I6, SQ_J6},

  std::vector<Square> {SQ_A5, SQ_B5, SQ_B6, SQ_A7, SQ_B7},
  std::vector<Square> {SQ_A5, SQ_B5, SQ_C5, SQ_A6, SQ_C6, SQ_A7, SQ_B7, SQ_C7},
  std::vector<Square> {SQ_B5, SQ_C5, SQ_D5, SQ_B6, SQ_D6, SQ_B7, SQ_C7, SQ_D7},
  std::vector<Square> {SQ_C5, SQ_D5, SQ_E5, SQ_C6, SQ_E6, SQ_C7, SQ_D7, SQ_E7},
  std::vector<Square> {SQ_D5, SQ_E5, SQ_F5, SQ_D6, SQ_F6, SQ_D7, SQ_E7, SQ_F7},
  std::vector<Square> {SQ_E5, SQ_F5, SQ_G5, SQ_E6, SQ_G6, SQ_E7, SQ_F7, SQ_G7},
  std::vector<Square> {SQ_F5, SQ_G5, SQ_H5, SQ_F6, SQ_H6, SQ_F7, SQ_G7, SQ_H7},
  std::vector<Square> {SQ_G5, SQ_H5, SQ_I5, SQ_G6, SQ_I6, SQ_G7, SQ_H7, SQ_I7},
  std::vector<Square> {SQ_H5, SQ_I5, SQ_J5, SQ_H6, SQ_J6, SQ_H7, SQ_I7, SQ_J7},
  std::vector<Square> {SQ_I5, SQ_J5, SQ_I6, SQ_I7, SQ_J7},

  std::vector<Square> {SQ_A6, SQ_B6, SQ_B7, SQ_A8, SQ_B8},
  std::vector<Square> {SQ_A6, SQ_B6, SQ_C6, SQ_A7, SQ_C7, SQ_A8, SQ_B8, SQ_C8},
  std::vector<Square> {SQ_B6, SQ_C6, SQ_D6, SQ_B7, SQ_D7, SQ_B8, SQ_C8, SQ_D8},
  std::vector<Square> {SQ_C6, SQ_D6, SQ_E6, SQ_C7, SQ_E7, SQ_C8, SQ_D8, SQ_E8},
  std::vector<Square> {SQ_D6, SQ_E6, SQ_F6, SQ_D7, SQ_F7, SQ_D8, SQ_E8, SQ_F8},
  std::vector<Square> {SQ_E6, SQ_F6, SQ_G6, SQ_E7, SQ_G7, SQ_E8, SQ_F8, SQ_G8},
  std::vector<Square> {SQ_F6, SQ_G6, SQ_H6, SQ_F7, SQ_H7, SQ_F8, SQ_G8, SQ_H8},
  std::vector<Square> {SQ_G6, SQ_H6, SQ_I6, SQ_G7, SQ_I7, SQ_G8, SQ_H8, SQ_I8},
  std::vector<Square> {SQ_H6, SQ_I6, SQ_J6, SQ_H7, SQ_J7, SQ_H8, SQ_I8, SQ_J8},
  std::vector<Square> {SQ_I6, SQ_J6, SQ_I7, SQ_I8, SQ_J8},

  std::vector<Square> {SQ_A7, SQ_B7, SQ_B8},
  std::vector<Square> {SQ_A7, SQ_B7, SQ_C7, SQ_A8, SQ_C8},
  std::vector<Square> {SQ_B7, SQ_C7, SQ_D7, SQ_B8, SQ_D8},
  std::vector<Square> {SQ_C7, SQ_D7, SQ_E7, SQ_C8, SQ_E8},
  std::vector<Square> {SQ_D7, SQ_E7, SQ_F7, SQ_D8, SQ_F8},
  std::vector<Square> {SQ_E7, SQ_F7, SQ_G7, SQ_E8, SQ_G8},
  std::vector<Square> {SQ_F7, SQ_G7, SQ_H7, SQ_F8, SQ_H8},
  std::vector<Square> {SQ_G7, SQ_H7, SQ_I7, SQ_G8, SQ_I8},
  std::vector<Square> {SQ_H7, SQ_I7, SQ_J7, SQ_H8, SQ_J8},
  std::vector<Square> {SQ_I7, SQ_J7, SQ_I8} 
};

//TODO calculate this at compile time with a loop
const std::array<Bitboard, NUM_SQUARES> MOVE_BB = {
  bbFromVec(MOVE_LIST[SQ_A1]),
  bbFromVec(MOVE_LIST[SQ_B1]),
  bbFromVec(MOVE_LIST[SQ_C1]),
  bbFromVec(MOVE_LIST[SQ_D1]),
  bbFromVec(MOVE_LIST[SQ_E1]),
  bbFromVec(MOVE_LIST[SQ_F1]),
  bbFromVec(MOVE_LIST[SQ_G1]),
  bbFromVec(MOVE_LIST[SQ_H1]),
  bbFromVec(MOVE_LIST[SQ_I1]),
  bbFromVec(MOVE_LIST[SQ_J1]),

  bbFromVec(MOVE_LIST[SQ_A2]),
  bbFromVec(MOVE_LIST[SQ_B2]),
  bbFromVec(MOVE_LIST[SQ_C2]),
  bbFromVec(MOVE_LIST[SQ_D2]),
  bbFromVec(MOVE_LIST[SQ_E2]),
  bbFromVec(MOVE_LIST[SQ_F2]),
  bbFromVec(MOVE_LIST[SQ_G2]),
  bbFromVec(MOVE_LIST[SQ_H2]),
  bbFromVec(MOVE_LIST[SQ_I2]),
  bbFromVec(MOVE_LIST[SQ_J2]),

  bbFromVec(MOVE_LIST[SQ_A3]),
  bbFromVec(MOVE_LIST[SQ_B3]),
  bbFromVec(MOVE_LIST[SQ_C3]),
  bbFromVec(MOVE_LIST[SQ_D3]),
  bbFromVec(MOVE_LIST[SQ_E3]),
  bbFromVec(MOVE_LIST[SQ_F3]),
  bbFromVec(MOVE_LIST[SQ_G3]),
  bbFromVec(MOVE_LIST[SQ_H3]),
  bbFromVec(MOVE_LIST[SQ_I3]),
  bbFromVec(MOVE_LIST[SQ_J3]),

  bbFromVec(MOVE_LIST[SQ_A4]),
  bbFromVec(MOVE_LIST[SQ_B4]),
  bbFromVec(MOVE_LIST[SQ_C4]),
  bbFromVec(MOVE_LIST[SQ_D4]),
  bbFromVec(MOVE_LIST[SQ_E4]),
  bbFromVec(MOVE_LIST[SQ_F4]),
  bbFromVec(MOVE_LIST[SQ_G4]),
  bbFromVec(MOVE_LIST[SQ_H4]),
  bbFromVec(MOVE_LIST[SQ_I4]),
  bbFromVec(MOVE_LIST[SQ_J4]),

  bbFromVec(MOVE_LIST[SQ_A5]),
  bbFromVec(MOVE_LIST[SQ_B5]),
  bbFromVec(MOVE_LIST[SQ_C5]),
  bbFromVec(MOVE_LIST[SQ_D5]),
  bbFromVec(MOVE_LIST[SQ_E5]),
  bbFromVec(MOVE_LIST[SQ_F5]),
  bbFromVec(MOVE_LIST[SQ_G5]),
  bbFromVec(MOVE_LIST[SQ_H5]),
  bbFromVec(MOVE_LIST[SQ_I5]),
  bbFromVec(MOVE_LIST[SQ_J5]),

  bbFromVec(MOVE_LIST[SQ_A6]),
  bbFromVec(MOVE_LIST[SQ_B6]),
  bbFromVec(MOVE_LIST[SQ_C6]),
  bbFromVec(MOVE_LIST[SQ_D6]),
  bbFromVec(MOVE_LIST[SQ_E6]),
  bbFromVec(MOVE_LIST[SQ_F6]),
  bbFromVec(MOVE_LIST[SQ_G6]),
  bbFromVec(MOVE_LIST[SQ_H6]),
  bbFromVec(MOVE_LIST[SQ_I6]),
  bbFromVec(MOVE_LIST[SQ_J6]),

  bbFromVec(MOVE_LIST[SQ_A7]),
  bbFromVec(MOVE_LIST[SQ_B7]),
  bbFromVec(MOVE_LIST[SQ_C7]),
  bbFromVec(MOVE_LIST[SQ_D7]),
  bbFromVec(MOVE_LIST[SQ_E7]),
  bbFromVec(MOVE_LIST[SQ_F7]),
  bbFromVec(MOVE_LIST[SQ_G7]),
  bbFromVec(MOVE_LIST[SQ_H7]),
  bbFromVec(MOVE_LIST[SQ_I7]),
  bbFromVec(MOVE_LIST[SQ_J7]),

  bbFromVec(MOVE_LIST[SQ_A8]),
  bbFromVec(MOVE_LIST[SQ_B8]),
  bbFromVec(MOVE_LIST[SQ_C8]),
  bbFromVec(MOVE_LIST[SQ_D8]),
  bbFromVec(MOVE_LIST[SQ_E8]),
  bbFromVec(MOVE_LIST[SQ_F8]),
  bbFromVec(MOVE_LIST[SQ_G8]),
  bbFromVec(MOVE_LIST[SQ_H8]),
  bbFromVec(MOVE_LIST[SQ_I8]),
  bbFromVec(MOVE_LIST[SQ_J8])
};

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
 */
