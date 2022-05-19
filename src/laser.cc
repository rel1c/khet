#include "laser.h"

/**
 * @brief Fires the laser!
 * @param b The board on which to fire the laser
 * @param s The board where to start the laser beam
 * @param d The initial direction of the laser beam
 * @return A captured piece
 */
const Capture Laser::fire(const Board& b, Square s, Direction d) {
  Color player = b.player(); 
  while (true) {
    Piece p = b.pieceOn(s);
    if (b.pieceOn(s)) {
      if ((~p | ~REFLECTOR_MASK) || 
          ()) {
        return (p << 7) | s;
      }
    }
    if (escaping()) {
      // break
    }
  }
}
