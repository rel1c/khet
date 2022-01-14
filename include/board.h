#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>

#include "bitboard.h"
#include "piececode.h"

namespace khet {

const unsigned int NUM_ANUBIS = 2;
const unsigned int NUM_PHARAOH = 1;
const unsigned int NUM_PYRAMID = 7;
const unsigned int NUM_SCARAB = 2;
const unsigned int NUM_SPHINX = 1;

class Move; // forward declaration

enum Layout {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

enum Rotation {
  POSITIVE = 1,
  NEGATIVE = -1
};

class Board {
public:
  Board();
  Board(Layout);
  Board(const std::string&);

  void setToPkn(const std::string&);
  const std::string toPkn() const;
  bool isLegal() const;

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

  void doMove(const Move&);
  void undoMove(const Move&);
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

  Color _player = SILVER;
  unsigned int _turn = 0;

  std::array<PieceCode, NSQUARES> _pieces;

  bool _verifyPkn(const std::string&);

  void _addPiece(Square, Color, Direction, Piece);
  void _movePiece(Square, Square);
  void _swapPieces(Square, Square);
  void _rotatePiece(Square, Rotation);
  void _removePiece(Square);

  Bitboard& _getColorRef(Color);
  Bitboard& _getDirectionRef(Direction);
  Bitboard& _getPieceRef(Piece);

  Bitboard& _getColorRefAt(Square s);
  Bitboard& _getDirectionRefAt(Square s);
  Bitboard& _getPieceRefAt(Square s);
};

} // namespace khet

#endif
