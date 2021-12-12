#include "movegen.h"
#include "util.h"

namespace khet {

MoveGen::MoveGen() {}

MoveGen::MoveGen(const Board &board) {}

Moves MoveGen::getMoves() const {
  return _moves;
}

void MoveGen::setBoard(const Board &board) {
}

const std::array<Squares, NSQUARES> MoveGen::_lookup_sqrs = {
  Squares {A2, B1, B2},                     // A1
  Squares {A1, A2, B2, C1, C2},             // B1
  Squares {B1, B2, C2, D1, D2},             // C1
  Squares {C1, C2, D2, E1, E2},             // D1
  Squares {D1, D2, E2, F1, F2},             // E1
  Squares {E1, E2, F2, G1, G2},             // F1
  Squares {F1, F2, G2, H1, H2},             // G1
  Squares {G1, G2, H2, I1, I2},             // H1
  Squares {H1, H2, I2, J1, J2},             // I1
  Squares {I1, I2, J2},                     // J1

  Squares {A1, A3, B1, B2, B3},             // A2
  Squares {A1, A2, A3, B1, B3, C1, C2, C3}, // B2
  Squares {B1, B2, B3, C1, C3, D1, D2, D3}, // C2
  Squares {C1, C2, C3, D1, D3, E1, E2, E3}, // D2
  Squares {D1, D2, D3, E1, E3, F1, F2, F3}, // E2
  Squares {E1, E2, E3, F1, F3, G1, G2, G3}, // F2
  Squares {F1, F2, F3, G1, G3, H1, H2, H3}, // G2
  Squares {G1, G2, G3, H1, H3, I1, I2, I3}, // H2
  Squares {H1, H2, H3, I1, I3, J1, J2, J3}, // I2
  Squares {I1, I2, I3, J1, J3},             // J2

  Squares {A2, A4, B2, B3, B4},             // A3
  Squares {A2, A3, A4, B2, B4, C2, C3, C4}, // B3
  Squares {B2, B3, B4, C2, C4, D2, D3, D4}, // C3
  Squares {C2, C3, C4, D2, D4, E2, E3, E4}, // D3
  Squares {D2, D3, D4, E2, E4, F2, F3, F4}, // E3
  Squares {E2, E3, E4, F2, F4, G2, G3, G4}, // F3
  Squares {F2, F3, F4, G2, G4, H2, H3, H4}, // G3
  Squares {G2, G3, G4, H2, H4, I2, I3, I4}, // H3
  Squares {H2, H3, H4, I2, I4, J2, J3, J4}, // I3
  Squares {I2, I3, I4, J2, J4},             // J3

  Squares {A3, A5, B3, B4, B5},             // A4
  Squares {A3, A4, A5, B3, B5, C3, C4, C5}, // B4
  Squares {B3, B4, B5, C3, C5, D3, D4, D5}, // C4
  Squares {C3, C4, C5, D3, D5, E3, E4, E5}, // D4
  Squares {D3, D4, D5, E3, E5, F3, F4, F5}, // E4
  Squares {E3, E4, E5, F3, F5, G3, G4, G5}, // F4
  Squares {F3, F4, F5, G3, G5, H3, H4, H5}, // G4
  Squares {G3, G4, G5, H3, H5, I3, I4, I5}, // H4
  Squares {H3, H4, H5, I3, I5, J3, J4, J5}, // I4
  Squares {I3, I4, I5, J3, J5},             // J4

  Squares {A4, A6, B4, B5, B6},             // A5
  Squares {A4, A5, A6, B4, B6, C4, C5, C6}, // B5
  Squares {B4, B5, B6, C4, C6, D4, D5, D6}, // C5
  Squares {C4, C5, C6, D4, D6, E4, E5, E6}, // D5
  Squares {D4, D5, D6, E4, E6, F4, F5, F6}, // E5
  Squares {E4, E5, E6, F4, F6, G4, G5, G6}, // F5
  Squares {F4, F5, F6, G4, G6, H4, H5, H6}, // G5
  Squares {G4, G5, G6, H4, H6, I4, I5, I6}, // H5
  Squares {H4, H5, H6, I4, I6, J4, J5, J6}, // I5
  Squares {I4, I5, I6, J4, J6},             // J5

  Squares {A5, A7, B5, B6, B7},             // A6
  Squares {A5, A6, A7, B5, B7, C5, C6, C7}, // B6
  Squares {B5, B6, B7, C5, C7, D5, D6, D7}, // C6
  Squares {C5, C6, C7, D5, D7, E5, E6, E7}, // D6
  Squares {D5, D6, D7, E5, E7, F5, F6, F7}, // E6
  Squares {E5, E6, E7, F5, F7, G5, G6, G7}, // F6
  Squares {F5, F6, F7, G5, G7, H5, H6, H7}, // G6
  Squares {G5, G6, G7, H5, H7, I5, I6, I7}, // H6
  Squares {H5, H6, H7, I5, I7, J5, J6, J7}, // I6
  Squares {I5, I6, I7, J5, J7},             // J6

  Squares {A6, A8, B6, B7, B8},             // A7
  Squares {A6, A7, A8, B6, B8, C6, C7, C8}, // B7
  Squares {B6, B7, B8, C6, C8, D6, D7, D8}, // C7
  Squares {C6, C7, C8, D6, D8, E6, E7, E8}, // D7
  Squares {D6, D7, D8, E6, E8, F6, F7, F8}, // E7
  Squares {E6, E7, E8, F6, F8, G6, G7, G8}, // F7
  Squares {F6, F7, F8, G6, G8, H6, H7, H8}, // G7
  Squares {G6, G7, G8, H6, H8, I6, I7, I8}, // H7
  Squares {H6, H7, H8, I6, I8, J6, J7, J8}, // I7
  Squares {I6, I7, I8, J6, J8},             // J7

  Squares {A7, B7, B8},                     // A8
  Squares {A7, A8, B7, C7, C8},             // B8
  Squares {B7, B8, C7, D7, D8},             // C8
  Squares {C7, C8, D7, E7, E8},             // D8
  Squares {D7, D8, E7, F7, F8},             // E8
  Squares {E7, E8, F7, G7, G8},             // F8
  Squares {F7, F8, G7, H7, H8},             // G8
  Squares {G7, G8, H7, I7, I8},             // H8
  Squares {H7, H8, I7, J7, J8},             // I8
  Squares {I7, I8, J7}                      // J8
};

const std::array<Bitboard, NSQUARES> MoveGen::_lookup_moves = {
  initBitboard(_lookup_sqrs[A1]),
  initBitboard(_lookup_sqrs[B1]),
  initBitboard(_lookup_sqrs[C1]),
  initBitboard(_lookup_sqrs[D1]),
  initBitboard(_lookup_sqrs[E1]),
  initBitboard(_lookup_sqrs[F1]),
  initBitboard(_lookup_sqrs[G1]),
  initBitboard(_lookup_sqrs[H1]),
  initBitboard(_lookup_sqrs[I1]),
  initBitboard(_lookup_sqrs[J1]),

  initBitboard(_lookup_sqrs[A2]),
  initBitboard(_lookup_sqrs[B2]),
  initBitboard(_lookup_sqrs[C2]),
  initBitboard(_lookup_sqrs[D2]),
  initBitboard(_lookup_sqrs[E2]),
  initBitboard(_lookup_sqrs[F2]),
  initBitboard(_lookup_sqrs[G2]),
  initBitboard(_lookup_sqrs[H2]),
  initBitboard(_lookup_sqrs[I2]),
  initBitboard(_lookup_sqrs[J2]),

  initBitboard(_lookup_sqrs[A3]),
  initBitboard(_lookup_sqrs[B3]),
  initBitboard(_lookup_sqrs[C3]),
  initBitboard(_lookup_sqrs[D3]),
  initBitboard(_lookup_sqrs[E3]),
  initBitboard(_lookup_sqrs[F3]),
  initBitboard(_lookup_sqrs[G3]),
  initBitboard(_lookup_sqrs[H3]),
  initBitboard(_lookup_sqrs[I3]),
  initBitboard(_lookup_sqrs[J3]),

  initBitboard(_lookup_sqrs[A4]),
  initBitboard(_lookup_sqrs[B4]),
  initBitboard(_lookup_sqrs[C4]),
  initBitboard(_lookup_sqrs[D4]),
  initBitboard(_lookup_sqrs[E4]),
  initBitboard(_lookup_sqrs[F4]),
  initBitboard(_lookup_sqrs[G4]),
  initBitboard(_lookup_sqrs[H4]),
  initBitboard(_lookup_sqrs[I4]),
  initBitboard(_lookup_sqrs[J4]),

  initBitboard(_lookup_sqrs[A5]),
  initBitboard(_lookup_sqrs[B5]),
  initBitboard(_lookup_sqrs[C5]),
  initBitboard(_lookup_sqrs[D5]),
  initBitboard(_lookup_sqrs[E5]),
  initBitboard(_lookup_sqrs[F5]),
  initBitboard(_lookup_sqrs[G5]),
  initBitboard(_lookup_sqrs[H5]),
  initBitboard(_lookup_sqrs[I5]),
  initBitboard(_lookup_sqrs[J5]),

  initBitboard(_lookup_sqrs[A6]),
  initBitboard(_lookup_sqrs[B6]),
  initBitboard(_lookup_sqrs[C6]),
  initBitboard(_lookup_sqrs[D6]),
  initBitboard(_lookup_sqrs[E6]),
  initBitboard(_lookup_sqrs[F6]),
  initBitboard(_lookup_sqrs[G6]),
  initBitboard(_lookup_sqrs[H6]),
  initBitboard(_lookup_sqrs[I6]),
  initBitboard(_lookup_sqrs[J6]),

  initBitboard(_lookup_sqrs[A7]),
  initBitboard(_lookup_sqrs[B7]),
  initBitboard(_lookup_sqrs[C7]),
  initBitboard(_lookup_sqrs[D7]),
  initBitboard(_lookup_sqrs[E7]),
  initBitboard(_lookup_sqrs[F7]),
  initBitboard(_lookup_sqrs[G7]),
  initBitboard(_lookup_sqrs[H7]),
  initBitboard(_lookup_sqrs[I7]),
  initBitboard(_lookup_sqrs[J7]),

  initBitboard(_lookup_sqrs[A8]),
  initBitboard(_lookup_sqrs[B8]),
  initBitboard(_lookup_sqrs[C8]),
  initBitboard(_lookup_sqrs[D8]),
  initBitboard(_lookup_sqrs[E8]),
  initBitboard(_lookup_sqrs[F8]),
  initBitboard(_lookup_sqrs[G8]),
  initBitboard(_lookup_sqrs[H8]),
  initBitboard(_lookup_sqrs[I8]),
  initBitboard(_lookup_sqrs[J8])
};

const std::array<Rotation, 4> MoveGen::_sphinxRotations {
  NEGATIVE, // Silver sphinx facing north
  POSITIVE, // Red sphinx facing east
  NEGATIVE, // Silver sphinx facing south
  POSITIVE  // Red sphinx facing west
};

/**
 * @brief
 * @param turn
 */
void MoveGen::_genMoves(const Board& b) {
  _moves.clear();
  Bitboard pieces;
  if (b.getPlayer() == RED)
    pieces = b.getColor(RED);
  else
    pieces = b.getColor(SILVER);
  for (int i = 0; i < NSQUARES; i++) {
    if (pieces[i]) {
      Square s = static_cast<Square>(i);
      // If piece is sphinx, generate sphinx rotation
      if (b.getPiece(SPHINX)[s]) {
        _genSphinxRotation(b, s);
        continue;
      }
      // If piece is scarab, generate swap moves
      else if (b.getPiece(SCARAB)[s]) {
        _genSwaps(b, s);
      }
      // Generate basic moves
      Bitboard able = _lookup_moves[s] & ~b.getAllPieces();
      for (Square t : _lookup_sqrs[s]) {
        if (able[t]) {
          _moves.push_back(Move(s, t));
        }
      }
      // Generate rotations
      _moves.push_back(Move(s, POSITIVE));
      _moves.push_back(Move(s, NEGATIVE));
    }
  }
}

void MoveGen::_genSwaps(const Board& b, Square s) {
  Bitboard able = _lookup_moves[s] & b.getSwappable();
  bool swap = true;
  for (Square t : _lookup_sqrs[s]) {
    if (able[t]) {
      _moves.push_back(Move(s, t, swap));
    }
  }
}

void MoveGen::_genSphinxRotation(const Board& b, Square s) {
  Direction d = b.getDirectionAt(s);
  Rotation r = _sphinxRotations[d];
  _moves.push_back(Move(s, r));
}

} // namespace khet