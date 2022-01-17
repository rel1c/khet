#include "board.h"

Bitboard Board::pieces() const {
  return Bitboard(0); //TODO

}

Bitboard Board::pieces(PieceType pt) const {
  return Bitboard(0); //TODO

}

Bitboard Board::pieces(Color c) const {
  return Bitboard(0); //TODO

}

Bitboard Board::pieces(Direction d) const {
  return Bitboard(0); //TODO

}

Piece Board::pieceOn(Square s) const {
  return NO_PIECE; //TODO

}

void Board::fromPkn(const std::string&) {
} //TODO

const std::string Board::toPkn() const {
  return ""; //TODO
}

//void Board::doMove(const Move&) {
//}

//void Board::undoMove(const Move&) {
//}

void Board::display() const {
} //TODO
