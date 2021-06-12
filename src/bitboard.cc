/**
 * @file bitboard.cc
 */

#include "bitboard.h"

namespace khet {

const Bitboard Bitlogic::board_empty = Bitboard(0);
const Bitboard Bitlogic::board_full = Bitboard(~board_empty);

} // namespace khet
