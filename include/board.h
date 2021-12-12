#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>

#include "bitboard.h"
#include "layout.h"

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

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
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

  Color getColorAt(Square) const;
  Direction getDirectionAt(Square) const;
  Piece getPieceAt(Square) const;

  Bitboard getAllPieces() const;
  Bitboard getSwappable() const;

  Color getPlayer() const;

  void doMove(Move); //TODO
private:
  static const Bitboard _red_sqrs;
  static const Bitboard _silver_sqrs;
  static const Bitboard _empty;
  static const Bitboard _full;
  static const Bitboard _sphinx;

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

  Color _player;
  unsigned int _turn;

  void _addPiece(Square, Color, Direction, Piece); //TODO
  void _movePiece(Square, Square); //TODO
  void _removePiece(Square); //TODO
  void _updateBitboards(); //TODO
};

} // namespace khet

#endif
