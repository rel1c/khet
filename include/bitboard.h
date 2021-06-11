/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <bitset>
#include <iostream>
#include <cassert>

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
  Bitboard(std::string& bitstr) {
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

  // Access square of board with Cartesian coordinates
  bool get(int x, int y) {
    assert(0 <= y && y < ROW);
    assert(0 <= x && x < COL);
    return bits[COL*y + x];
  }

  // Assign square of board with Cartesian coordinates
  void set(int x, int y, bool val) {
    assert(0 <= y && y < ROW);
    assert(0 <= x && x < COL);
    bits[COL*y + x] = val;
  }

  // Access square of board with alphanumeric coordinates
  bool get(char cha, char chn) {
    assert(isalpha(cha));
    assert(isdigit(chn));
    int x = cha - 97;
    int y = chn - 49;
    assert(0 <= y && y < ROW);
    assert(0 <= x && x < COL);
    return bits[COL*y + x];
  }

  // Assign square of board with alphanumeric coordinates
  void set(char cha, char chn, bool val) {
    assert(isalpha(cha));
    assert(isdigit(chn));
    int x = cha - 97;
    int y = chn - 49;
    assert(0 <= y && y < ROW);
    assert(0 <= x && x < COL);
    bits[COL*y + x] = val;
  }

  // Set board to all true or false
  void setAll(bool val) {
    if (val)
      bits.set();
    else
      bits.reset();
  }

  // Logical OR operator overload
  Bitboard& operator|(const Bitboard& b) {
    bits |= b.bits;
    return *this;
  }

  // Send bitboard to standard out
  friend std::ostream& operator<<(std::ostream& os, const Bitboard& b) {
    std::string str = b.bits.to_string();
    return os << str;
  }

  // Pretty printer for bitboard
  void display() const {
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
