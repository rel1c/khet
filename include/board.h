#include <bitset>
#include "piece.h"

#ifndef BOARD_H_
#define BOARD_H_

const unsigned int NUM_FILES = 10;
const unsigned int NUM_RANKS = 8;
const unsigned int NUM_SQUARES = 80;

enum Square : unsigned int {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1, SQ_I1, SQ_J1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2, SQ_I2, SQ_J2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3, SQ_I3, SQ_J3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4, SQ_I4, SQ_J4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5, SQ_I5, SQ_J5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6, SQ_I6, SQ_J6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7, SQ_I7, SQ_J7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8, SQ_I8, SQ_J8,
  SQ_NONE
};

enum Rank : unsigned int {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

enum File : unsigned int {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_I, FILE_J
};

constexpr File fileOf(Square s) {
  return File(s % NUM_FILES);
}

constexpr Rank rankOf(Square s) {
  return Rank(s / NUM_FILES);
}

using Bitboard = std::bitset <NUM_SQUARES>;

class Board {
public:
  Board() = default;
  Board(const Board&) = delete;
  Board& operator=(const Board&) = delete;

  void fromPkn(const std::string&);
  const std::string toPkn() const;

  Bitboard pieces() const;
  Bitboard pieces(PieceType pt) const;
  Bitboard pieces(Color c) const;
  Bitboard pieces(Direction d) const;
  Piece pieceOn(Square s) const;
  Color player() const;

  void addPiece(Square, Color, PieceType, Direction);
  void removePiece(Square);
  void movePiece(Square, Square);
  void swapPiece(Square, Square);
  void rotatePiece(Square, Rotation);

  //void doMove(const Move&);
  //void undoMove(const Move&);

  void display() const;

private:
  Piece _pieces[NUM_SQUARES];
  Bitboard _color_bb[NUM_COLORS];
  Bitboard _direction_bb[NUM_DIRECTIONS];
  Bitboard _type_bb[NUM_PIECE_TYPES];
  Color _player;
  std::string _pkn;
  unsigned int _turn;
};

inline Bitboard Board::pieces() const {
  return _type_bb[ALL_PIECES];
}

inline Bitboard Board::pieces(PieceType pt) const {
  return _type_bb[pt];
}

inline Bitboard Board::pieces(Color c) const {
  return _color_bb[c];
}

inline Bitboard Board::pieces(Direction d) const {
  return _direction_bb[d];
}

inline Piece Board::pieceOn(Square s) const {
  return _pieces[s];
}

inline Color Board::player() const {
  return _player;
}

inline void addPiece(Square s, Color c, PieceType pt, Direction d) {} //TODO
inline void removePiece(Square s) {} //TODO
inline void movePiece(Square from, Square to) {} //TODO
inline void swapPiece(Square from, Square to) {} //TODO
inline void rotatePiece(Square s, Rotation r) {} //TODO

#endif
