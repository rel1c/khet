#include <iostream>
#include <sstream>

#include "board.h"

const Bitboard FILE_BB_A = bbFromVec(std::vector<Square> {
  SQ_A1, SQ_A2, SQ_A3, SQ_A4, SQ_A5, SQ_A6, SQ_A7, SQ_A8
});
const Bitboard FILE_BB_B = FILE_BB_A << 1;
const Bitboard FILE_BB_C = FILE_BB_A << 2;
const Bitboard FILE_BB_D = FILE_BB_A << 3;
const Bitboard FILE_BB_E = FILE_BB_A << 4;
const Bitboard FILE_BB_F = FILE_BB_A << 5;
const Bitboard FILE_BB_G = FILE_BB_A << 6;
const Bitboard FILE_BB_H = FILE_BB_A << 7;
const Bitboard FILE_BB_I = FILE_BB_A << 8;
const Bitboard FILE_BB_J = FILE_BB_A << 9;

const Bitboard RANK_BB_1 = bbFromVec(std::vector<Square> {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1, SQ_I1, SQ_J1
});
const Bitboard RANK_BB_2 = RANK_BB_1 << (NUM_FILES * 1);
const Bitboard RANK_BB_3 = RANK_BB_1 << (NUM_FILES * 2);
const Bitboard RANK_BB_4 = RANK_BB_1 << (NUM_FILES * 3);
const Bitboard RANK_BB_5 = RANK_BB_1 << (NUM_FILES * 4);
const Bitboard RANK_BB_6 = RANK_BB_1 << (NUM_FILES * 5);
const Bitboard RANK_BB_7 = RANK_BB_1 << (NUM_FILES * 6);
const Bitboard RANK_BB_8 = RANK_BB_1 << (NUM_FILES * 7);

const std::array<Bitboard, NUM_SQUARES> SQ_BB {
  FILE_BB_A & RANK_BB_1,
  FILE_BB_B & RANK_BB_1,
  FILE_BB_C & RANK_BB_1,
  FILE_BB_D & RANK_BB_1,
  FILE_BB_E & RANK_BB_1,
  FILE_BB_F & RANK_BB_1,
  FILE_BB_G & RANK_BB_1,
  FILE_BB_H & RANK_BB_1,
  FILE_BB_I & RANK_BB_1,
  FILE_BB_J & RANK_BB_1,

  FILE_BB_A & RANK_BB_2,
  FILE_BB_B & RANK_BB_2,
  FILE_BB_C & RANK_BB_2,
  FILE_BB_D & RANK_BB_2,
  FILE_BB_E & RANK_BB_2,
  FILE_BB_F & RANK_BB_2,
  FILE_BB_G & RANK_BB_2,
  FILE_BB_H & RANK_BB_2,
  FILE_BB_I & RANK_BB_2,
  FILE_BB_J & RANK_BB_2,

  FILE_BB_A & RANK_BB_3,
  FILE_BB_B & RANK_BB_3,
  FILE_BB_C & RANK_BB_3,
  FILE_BB_D & RANK_BB_3,
  FILE_BB_E & RANK_BB_3,
  FILE_BB_F & RANK_BB_3,
  FILE_BB_G & RANK_BB_3,
  FILE_BB_H & RANK_BB_3,
  FILE_BB_I & RANK_BB_3,
  FILE_BB_J & RANK_BB_3,

  FILE_BB_A & RANK_BB_4,
  FILE_BB_B & RANK_BB_4,
  FILE_BB_C & RANK_BB_4,
  FILE_BB_D & RANK_BB_4,
  FILE_BB_E & RANK_BB_4,
  FILE_BB_F & RANK_BB_4,
  FILE_BB_G & RANK_BB_4,
  FILE_BB_H & RANK_BB_4,
  FILE_BB_I & RANK_BB_4,
  FILE_BB_J & RANK_BB_4,

  FILE_BB_A & RANK_BB_5,
  FILE_BB_B & RANK_BB_5,
  FILE_BB_C & RANK_BB_5,
  FILE_BB_D & RANK_BB_5,
  FILE_BB_E & RANK_BB_5,
  FILE_BB_F & RANK_BB_5,
  FILE_BB_G & RANK_BB_5,
  FILE_BB_H & RANK_BB_5,
  FILE_BB_I & RANK_BB_5,
  FILE_BB_J & RANK_BB_5,

  FILE_BB_A & RANK_BB_6,
  FILE_BB_B & RANK_BB_6,
  FILE_BB_C & RANK_BB_6,
  FILE_BB_D & RANK_BB_6,
  FILE_BB_E & RANK_BB_6,
  FILE_BB_F & RANK_BB_6,
  FILE_BB_G & RANK_BB_6,
  FILE_BB_H & RANK_BB_6,
  FILE_BB_I & RANK_BB_6,
  FILE_BB_J & RANK_BB_6,

  FILE_BB_A & RANK_BB_7,
  FILE_BB_B & RANK_BB_7,
  FILE_BB_C & RANK_BB_7,
  FILE_BB_D & RANK_BB_7,
  FILE_BB_E & RANK_BB_7,
  FILE_BB_F & RANK_BB_7,
  FILE_BB_G & RANK_BB_7,
  FILE_BB_H & RANK_BB_7,
  FILE_BB_I & RANK_BB_7,
  FILE_BB_J & RANK_BB_7,

  FILE_BB_A & RANK_BB_8,
  FILE_BB_B & RANK_BB_8,
  FILE_BB_C & RANK_BB_8,
  FILE_BB_D & RANK_BB_8,
  FILE_BB_E & RANK_BB_8,
  FILE_BB_F & RANK_BB_8,
  FILE_BB_G & RANK_BB_8,
  FILE_BB_H & RANK_BB_8,
  FILE_BB_I & RANK_BB_8,
  FILE_BB_J & RANK_BB_8,
};

/**
 * @brief Initialize a bitboard with a vector of board squares.
 * @param v The vector
 */
Bitboard bbFromVec(const std::vector<Square>& v) {
  Bitboard bb;
  for (auto& s : v) {
    bb.set(s);
  }
  return bb;
};

/**
 * @brief Display a bitboard as a Khet board, boardered by rank and file
 * notation, with starting square in the lower left, as seen by the silver
 * player.
 * @param bb The bitboard
 */
void display(const Bitboard& bb) {
  std::string bb_str = bb.to_string();
  for (int i = NUM_RANKS; i > 0; i--) {
    std::cout << i << " ";
    for (int j = 0; j < NUM_FILES; j++) {
      std::cout << bb[(i-1) * NUM_FILES + j];
    }
    std::cout << "\n";
  }
  std::cout << "  abcdefghij" << std::endl;
}

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
      Square s = static_cast<Square>(i++);
      addPiece(make(c, pt, d), s);
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
