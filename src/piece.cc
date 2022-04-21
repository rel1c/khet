#include "piece.h"

const std::string pieceToStr(Piece p) {
  if (p == NO_PIECE)
    return "NO_PIECE";
  Color c = colorOf(p);
  PieceType pt = typeOf(p);
  Direction d = directionOf(p);
  std::string c_str, pt_str, d_str;
  c_str = (c == RED) ? "RED_" : "SILVER_";
  switch(pt) {
    case ANUBIS:
      pt_str = "ANUBIS_"; break;
    case SPHINX:
      pt_str = "SPHINX_"; break;
    case PHARAOH:
      pt_str = "PHARAOH_"; break;
    case PYRAMID:
      pt_str = "PYRAMID_"; break;
    case SCARAB:
      pt_str = "SCARAB_"; break;
    case EYE_OF_HORUS:
      pt_str = "EYE_OF_HORUS_"; break;
  }
  switch(d) {
    case NORTH:
      d_str = "NORTH"; break;
    case WEST:
      d_str = "WEST"; break;
    case SOUTH:
      d_str = "SOUTH"; break;
    case EAST:
      d_str = "EAST"; break;
  }
  return c_str + pt_str + d_str;
}
