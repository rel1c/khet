/**
 * @file bitboard.h
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

namespace khet {

/**
 * @struct Bitboard
 * @brief A bitboard for the game of Khet.
 * @details This struct embodies the details of various Khet pieces and their
 *          possible actions in a 128-bit word using bit flags.
 */
struct Bitboard {
  unsigned __int128 b;
};

} // namespace khet

#endif
