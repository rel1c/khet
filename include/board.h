#include <array>
#include <bitset>
#include <vector>

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

Bitboard bbFromVec(const std::vector<Square>&);

void display(const Bitboard&);

extern const Bitboard FILE_BB_A;
extern const Bitboard FILE_BB_B;
extern const Bitboard FILE_BB_C;
extern const Bitboard FILE_BB_D;
extern const Bitboard FILE_BB_E;
extern const Bitboard FILE_BB_F;
extern const Bitboard FILE_BB_G;
extern const Bitboard FILE_BB_H;
extern const Bitboard FILE_BB_I;
extern const Bitboard FILE_BB_J;

extern const Bitboard RANK_BB_1;
extern const Bitboard RANK_BB_2;
extern const Bitboard RANK_BB_3;
extern const Bitboard RANK_BB_4;
extern const Bitboard RANK_BB_5;
extern const Bitboard RANK_BB_6;
extern const Bitboard RANK_BB_7;
extern const Bitboard RANK_BB_8;

extern const std::array<Bitboard, NUM_SQUARES> SQ_BB;

class Board {
public:
  Board() = default;

  void setPkn(const std::string&);
  const std::string toPkn() const;

  Bitboard pieces() const;
  Bitboard pieces(PieceType pt) const;
  Bitboard pieces(Color c) const;
  Bitboard pieces(Direction d) const;
  Piece pieceOn(Square s) const;
  Color player() const;

  void addPiece(Piece, Square);
  void removePiece(Piece, Square);
  void movePiece(Square, Square);
  void swapPiece(Square, Square);
  void rotatePiece(Square, Rotation);

  //void doMove(const Move&);
  //void undoMove(const Move&);

  void display() const;

private:
  std::array<Piece, NUM_SQUARES> _pieces = {};
  // TODO sort out these magic numbers for enum lengths
  std::array<Bitboard, 3> _color_bb = {};
  std::array<Bitboard, 4> _direction_bb = {};
  std::array<Bitboard, 8> _type_bb = {};
  Color _player = SILVER;
  std::string _pkn = "";
  unsigned int _turn = 0;
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

inline void Board::addPiece(Piece p, Square s) {
  _pieces[s] = p;
  _color_bb[colorOf(p)].set(s);
  _direction_bb[directionOf(p)].set(s);
  _type_bb[typeOf(p)].set(s);
  _type_bb[ALL_PIECES].set(s);
}

inline void Board::removePiece(Piece p, Square s) {
  _pieces[s] = NO_PIECE;
  _color_bb[colorOf(p)].reset(s);
  _direction_bb[directionOf(p)].reset(s);
  _type_bb[typeOf(p)].reset(s);
  _type_bb[ALL_PIECES].reset(s);
}

inline void Board::movePiece(Square from, Square to) {
  Bitboard both = SQ_BB[from] | SQ_BB[to];
  Piece p = _pieces[from];
  _pieces[to] = p;
  _pieces[from] = NO_PIECE;
  _color_bb[colorOf(p)] ^= both;
  _direction_bb[directionOf(p)] ^= both;
  _type_bb[typeOf(p)] ^= both;
  _type_bb[ALL_PIECES] ^= both;
}

inline void Board::swapPiece(Square from, Square to) {
  Piece a = _pieces[from];
  Piece b = _pieces[to];
  Piece tmp = a;
  _pieces[from] = b;
  _pieces[to] = tmp;

  Bitboard both = SQ_BB[from] | SQ_BB[to];
  Color ca = colorOf(a);
  Color cb = colorOf(b);
  if (ca != cb) {
    _color_bb[ca] ^= both;
    _color_bb[cb] ^= both;
  }
  Direction da = directionOf(a);
  Direction db = directionOf(b);
  if (da != db) {
    _direction_bb[da] ^= both;
    _direction_bb[db] ^= both;
  }
  PieceType pta = typeOf(a);
  PieceType ptb = typeOf(b);
  if (pta != ptb) {
    _type_bb[pta] ^= both;
    _type_bb[ptb] ^= both;
  }
}

inline void Board::rotatePiece(Square s, Rotation r) {} //TODO

#endif
