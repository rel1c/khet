#include <array>
#include <bitset>
#include <vector>

#include "move.h"

#ifndef BOARD_H_
#define BOARD_H_

using Bitboard = std::bitset <NUM_SQUARES>;

const unsigned int NUM_FILES = 10;
const unsigned int NUM_RANKS = 8;

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

//TODO wrap files and ranks into an array
// (also, they are not being used anywhere, are they needed?
// extern const std::array<Bitboard, NUM_FILES> FILE_BB;
// extern const std::array<Bitboard, NUM_RANKS> RANK_BB;

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

extern const Bitboard SILVER_SQR_BB;
extern const Bitboard RED_SQR_BB;

extern const std::array<Bitboard, NUM_SQUARES> SQ_BB;

Bitboard bbFromVec(const std::vector<Square>&);
std::vector<Square> vecFromBB(const Bitboard&);
void display(const Bitboard&);

struct BoardState {
  BoardState* prev;
  Bitboard silver_path;
  Bitboard red_path;
  std::array<Capture, 3> captured; // 3 max for 2 beam splitters
};

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
  unsigned int turn() const;

  Bitboard blocked() const;

  void addPiece(Piece, Square);
  void removePiece(Piece, Square);
  void movePiece(Square, Square);
  void swapPiece(Square, Square);
  void rotatePiece(Square, Rotation);

  void doMove(const Move);
  void undoMove(const Move);

  void display() const;

private:
  BoardState* _state;
  std::array<Piece, NUM_SQUARES> _pieces = {};
  std::array<Bitboard, NUM_COLORS> _color_bb = {};
  std::array<Bitboard, NUM_DIRECTIONS> _direction_bb = {};
  std::array<Bitboard, NUM_PIECE_TYPES> _type_bb = {};
  Color _player = SILVER;
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

inline unsigned int Board::turn() const {
  return _turn;
}

inline Bitboard Board::blocked() const {
  return (_player == RED) ? SILVER_SQR_BB : RED_SQR_BB;
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
  _type_bb[pta] ^= both;
  _type_bb[ptb] ^= both;
}

inline void Board::rotatePiece(Square s, Rotation r) {
  Piece p = _pieces[s];
  _direction_bb[directionOf(p)].reset(s);
  p = (r == POSITIVE) ? rotatePos(p) : rotateNeg(p);
  _pieces[s] = p;
  _direction_bb[directionOf(p)].set(s);
}

#endif
