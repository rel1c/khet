/**
 * @file bitboard.cc
 */

#include "bitboard.h"

namespace khet {

const Bitboard Bitlogic::boardEmpty = Bitboard(0);
const Bitboard Bitlogic::boardFull = Bitboard(~boardEmpty);
} // namespace khet
