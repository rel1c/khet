/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <bitset>
#include <cassert>
#include <iostream>

namespace khet {

const unsigned int ROW = 8;
const unsigned int COL = 10;

struct Bitboard {
  std::bitset<128> bits;

  // Default constructor
  Bitboard() {
    bits = 0;
  }

  // Bitset constructor
  Bitboard(std::bitset<128> b) {
    bits = b;
  }

  // Bitstring constructor
  Bitboard(std::string bitstr) {
    bits = std::bitset<128>(bitstr);
  }

  // Copy constructor
  Bitboard(const Bitboard& other) {
    bits = other.bits;
  }

  // Assignment operator
  Bitboard& operator=(const Bitboard& other) {
    bits = other.bits;
    return *this;
  }

  // Access square of board
  bool get(int x, int y) {
    assert(0 <= x && x < ROW);
    assert(0 <= y && y < COL);
    return bits[COL*x + y];
  }

  // Assign square of board
  void set(int x, int y, bool val) {
    assert(0 <= x && x < ROW);
    assert(0 <= y && y < COL);
    bits[COL*x + y] = val;
  }

  // Set board to all true or false
  void setAll(bool val) {
    if (val)
      bits.set();
    else
      bits.reset();
  }

  // Send bitboard to standard out
  friend std::ostream& operator<<(std::ostream& os, const Bitboard& b) {
    std::string str = b.bits.to_string();
    return os << str;
  }

  // Pretty printer for bitboard
  void display() {
    for (int i = ROW-1; i >= 0; i--) {
      for (int j = 0; j < COL; j++) {
        char ch = (bits[i*COL + j]) ? '1' : '0';
        std::cout << ch;
      }
      std::cout << std::endl;
    }
  }

};

} // namespace khet

#endif
