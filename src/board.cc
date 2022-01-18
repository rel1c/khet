#include <iostream>
#include <sstream>

#include "board.h"

void Board::setPkn(const std::string& pkn) {

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
  std::string piece_str, direction_str, player_str, turn_str;
  // construct piece and direction sub-strings
  int gap = 0;
  for (int i = 0; i < NUM_SQUARES; i++) {
    Square s = static_cast<Square>(i);
    Piece p = _pieces[s];
    if(!p)
      gap++;
    if (p || fileOf(s) == FILE_J) {
      if (gap) {
        // account for ten represented as '0' in PKN
        gap %= 10;
        piece_str += std::to_string(gap);
        gap = 0;
      }
      if (p) {
        char ch = toChar(typeOf(p));
        piece_str += (colorOf(p) == SILVER) ? std::toupper(ch) : ch;
        direction_str += toChar(directionOf(p));
      }
      if (s != SQ_J8 && fileOf(s) == FILE_J) {
        piece_str += '/';
      }
    }
  }
  // combine it all together
  player_str = (_player == RED) ? 'r' : 's';
  turn_str = std::to_string(_turn);
  return piece_str + ' ' + direction_str + ' ' + player_str + ' ' + turn_str;
}

//void Board::doMove(const Move&) {
//}

//void Board::undoMove(const Move&) {
//}

void Board::display() const {
} //TODO
