/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <bitset>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

namespace khet {

const unsigned int ROWS = 8;
const unsigned int COLS = 10;

typedef std::bitset<128> Bitboard;

class Bitlogic {
public:
  static const Bitboard board_empty;
  static const Bitboard board_full;

  // Access square of board with Cartesian coordinates
  static bool Get(Bitboard& board, int x, int y) {
    assert(0 <= y && y < ROWS);
    assert(0 <= x && x < COLS);
    return board[COLS*y + x];
  }

  // Assign square of board with Cartesian coordinates
  static void Set(Bitboard& board, int x, int y, bool val) {
    assert(0 <= y && y < ROWS);
    assert(0 <= x && x < COLS);
    board[COLS*y + x] = val;
  }

  // Access square of board with alphanumeric coordinates
  static bool Get(Bitboard& board, char cha, char chn) {
    assert(isalpha(cha));
    assert(isdigit(chn));
    int x = cha - 97;
    int y = chn - 49;
    assert(0 <= y && y < ROWS);
    assert(0 <= x && x < COLS);
    return board[COLS*y + x];
  }

  // Assign square of board with alphanumeric coordinates
  static void Set(Bitboard& board, char cha, char chn, bool val) {
    assert(isalpha(cha));
    assert(isdigit(chn));
    int x = cha - 97;
    int y = chn - 49;
    assert(0 <= y && y < ROWS);
    assert(0 <= x && x < COLS);
    board[COLS*y + x] = val;
  }

  // Set board to all true or false
  static void SetAll(Bitboard& board, bool val) {
    if (val)
      board.set();
    else
      board.reset();
  }

  // Create board for a vector of coordinates
  static Bitboard CreateBoard(std::vector<std::string> coords);

  // Pretty printer for bitboard
  static void Display(Bitboard board);
};

} // namespace khet

#endif
