#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>

#include "bitboard.h"

namespace khet {

class Move; // forward declaration

enum Color {
  RED,
  SILVER,
};

enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

enum Layout {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

enum Rotation {
  POSITIVE = 1,
  NEGATIVE = -1
};

class Board {
public:
  Board();
  Board(Layout);
  Board(std::string);

  void setToPkn(std::string);

  Bitboard getColor(Color) const;
  Bitboard getDirection(Direction) const;
  Bitboard getPiece(Piece) const;

  bool isPieceAt(Square) const;
  Color getColorAt(Square) const;
  Direction getDirectionAt(Square) const;
  Piece getPieceAt(Square) const;

  Bitboard getAllPieces() const;
  Bitboard getSwappable() const;

  Color getPlayer() const;

  void doMove(Move); //TODO
  void display() const;
private:
  static const Bitboard _red_sqrs;
  static const Bitboard _silver_sqrs;
  static const Bitboard _empty;
  static const Bitboard _full;

  Bitboard _red;
  Bitboard _silver;

  Bitboard _north;
  Bitboard _east;
  Bitboard _south;
  Bitboard _west;

  Bitboard _anubis;
  Bitboard _pharaoh;
  Bitboard _pyramid;
  Bitboard _scarab;
  Bitboard _sphinx;

  Color _player;
  unsigned int _turn;

  void _addPiece(Square, Color, Direction, Piece);
  void _movePiece(Square, Square);
  void _swapPieces(Square, Square);
  void _rotatePiece(Square, Rotation);
  void _removePiece(Square);

  Bitboard& getColorRef(Color);
  Bitboard& getDirectionRef(Direction);
  Bitboard& getPieceRef(Piece);
};

} // namespace khet

#endif
