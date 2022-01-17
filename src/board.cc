#include <iostream>
#include <sstream>

#include "board.h"

void Board::fromPkn(const std::string& pkn) {

  // extract fields
  std::istringstream iss(pkn);
  std::string piece_str, direction_str, player_str, turn_str;
  getline(iss, piece_str, ' ');
  getline(iss, direction_str, ' ');
  getline(iss, player_str, ' ');
  getline(iss, turn_str, ' ');

  // initialize board with values
  Color c;
  Direction d;
  PieceType pt;
  auto p_ptr = piece_str.cbegin();
  auto d_ptr = direction_str.cbegin();
  int i = 0;

  // walk through both piece and direction "stacks"
  while (p_ptr != piece_str.cend() && d_ptr != direction_str.cend()) {
    if (isdigit(*p_ptr)) {
      if (*p_ptr == '0')
        i += 10;
      else
        i += *p_ptr - '0';
    }
    else if (*p_ptr != '/') {
      c = (isupper(*p_ptr)) ? SILVER : RED;
      pt = pieceTypeFromChar(*p_ptr);
      d = directionFromChar(*d_ptr);
      Square square = static_cast<Square>(i++);
      addPiece(square, c, pt, d);
      d_ptr++;
    }
    p_ptr++;
  }
  _player = (player_str == "r") ? RED : SILVER;
  _turn = std::stoi(turn_str);
}

const std::string Board::toPkn() const {
  return ""; //TODO
}

//void Board::doMove(const Move&) {
//}

//void Board::undoMove(const Move&) {
//}

void Board::display() const {
} //TODO
