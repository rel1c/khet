#include "piececode.h"

namespace khet {

PieceCode::PieceCode(Color c, Piece p, Direction d) {
  color = c;
  piece = p;
  direction = d;
}

std::ostream& operator<<(std::ostream& os, const PieceCode& pc) {
  return os << pc.color << ":" << pc.piece << ":" << pc.direction;
}

} // namespace khet
