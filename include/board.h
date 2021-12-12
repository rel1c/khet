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

enum Piece {
  ANUBIS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

class Board {
public:
  Board();
  Board(Layout);
  Board(std::string);

  /**
   * @brief Set the board to specific PKN string.
   * @param pkn PKN string
   */
  void setToPkn(std::string); //TODO

  Bitboard getColor(Color) const;
  Bitboard getDirection(Direction) const;
  Bitboard getPiece(Piece) const;

  Color getColorAt(Square) const; //TODO
  Direction getDirectionAt(Square) const; //TODO
  Piece getPieceAt(Square) const; //TODO

  Bitboard getAllPieces() const; //TODO
  Bitboard getSwappable() const; //TODO

  Color getPlayer() const; //TODO

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

  void _addPiece(); //TODO
  void _movePiece(); //TODO
  void _removePiece(); //TODO
  void _updateBitboards(); //TODO
};

} // namespace khet

#endif
