/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <cstdint>

namespace khet {

/**
 * @struct Bitboard
 * @brief A bitboard for the game of Khet.
 * @details This struct embodies the details of various Khet pieces and their
 *          possible actions in a 128-bit word using bit flags.
 */
struct Bitboard {
  unsigned __int128 b;

  // Numerical assignment operator
  Bitboard& operator=(const unsigned __int128 n) {
    b = n;
    return *this;
  }

  // Indexing operator, for element access
  uint8_t operator[](uint8_t i) const {
    return (b >> i) & 1;
  }
};

} // namespace khet

#endif
