#include "board.h"

/**
 * @brief Fires the laser!
 * @param b The board on which to fire the laser
 * @param s The board where to start the laser beam
 * @param d The initial direction of the laser beam
 * @return A captured piece
 * TODO This is the most naive and quick implementation I could put together!
 *      There exist a myriad of optimizations, but I need a model to test.
 */
const Capture Laser::fire(const Board& b, Square s, Direction ld) {
  s = _advance(s, ld);
  while(s != SQ_NONE) {
    Piece p = b.pieceOn(s);
    if (p) {
      Direction d = directionOf(p);
      PieceType pt = typeOf(p);
      // if blocking anubis, then stop
      if (pt == ANUBIS && d == (ld ^ 2)) {
        break;
      }
      // if piece is not reflector or pyramid and vulnerable
      else if (!(p & REFLECTOR_MASK) ||
              (pt == PYRAMID && _elimPyramid(ld, d))) {
        // return captured piece
        return makeCapture(p, s);
      }
      // must be reflecting
      // TODO nevermind beam splitting for now...
      else {
        assert(p & REFLECTOR_MASK);
        assert(pt == PYRAMID || pt == SCARAB || pt == EYE_OF_HORUS);
        ld = _reflect(ld, p);
      }
    }
    // TODO store path in member BBs and lists
    s = _advance(s, ld);
  }
  return NO_CAPTURE;
}
