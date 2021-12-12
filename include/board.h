#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>

#include "bitboard.h"
#include "layout.h"
#include "move.h"

namespace khet {

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
  Board(Layout); //TODO
  Board(std::string); //TODO

  /**
   * @brief Set the board to specific PKN string.
   * @param pkn PKN string
   */
  void setToPkn(std::string); //TODO

  Bitboard& getColor(Color) const;
  Bitboard& getDirection(Direction) const;
  Bitboard& getPiece(Piece) const;

  Bitboard& getColorAtSquare(Square) const; //TODO
  Bitboard& getDirectionAtSquare(Square) const; //TODO
  Bitboard& getPieceAtSquare(Square) const; //TODO

  Bitboard& getAllPieces() const; //TODO

  Color getPlayer() const; //TODO

  void doMove(Move); //TODO
private:
  static const std::array<std::vector<Square>, NSQUARES> moves_sqrs;
  static const std::array<Bitboard, NSQUARES> moves;

  static const Bitboard squares_red;
  static const Bitboard squares_silver;

  static const Bitboard empty;
  static const Bitboard full;

  static const Bitboard sphinx;

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

  void _updateBitboards(); //TODO

  void _addPiece(); //TODO
  void _movePiece(); //TODO
  void _removePiece(); //TODO
};

} // namespace khet

#endif
