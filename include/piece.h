#include <cassert>
#include <ostream>

#ifndef PIECE_H_
#define PIECE_H_

const unsigned int NUM_DIRECTIONS = 4;
const unsigned int MAX_MOVES = 121;
const unsigned int COLOR_MASK = 0b1100000;
const unsigned int PIECE_MASK = 0b11100;
const unsigned int REFLECTOR_MASK = 0b10000;

enum Color : unsigned int {
  NO_COLOR,
  SILVER,
  RED
};

enum Direction : unsigned int {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

enum PieceType : unsigned int {
  NO_PIECE_TYPE,
  ANUBIS,
  SPHINX,
  PHARAOH,
  PYRAMID,
  SCARAB,
  EYE_OF_HORUS
};

enum Piece : unsigned int {
  NO_PIECE,
  SILVER_ANUBIS_NORTH       = SILVER << 5 | ANUBIS       << 2 | NORTH,
  SILVER_ANUBIS_EAST        = SILVER << 5 | ANUBIS       << 2 | EAST,
  SILVER_ANUBIS_SOUTH       = SILVER << 5 | ANUBIS       << 2 | SOUTH,
  SILVER_ANUBIS_WEST        = SILVER << 5 | ANUBIS       << 2 | WEST,
  SILVER_EYE_OF_HORUS_NORTH = SILVER << 5 | EYE_OF_HORUS << 2 | NORTH,
  SILVER_EYE_OF_HORUS_EAST  = SILVER << 5 | EYE_OF_HORUS << 2 | EAST,
  SILVER_EYE_OF_HORUS_SOUTH = SILVER << 5 | EYE_OF_HORUS << 2 | SOUTH,
  SILVER_EYE_OF_HORUS_WEST  = SILVER << 5 | EYE_OF_HORUS << 2 | WEST,
  SILVER_PHARAOH_NORTH      = SILVER << 5 | PHARAOH      << 2 | NORTH,
  SILVER_PHARAOH_EAST       = SILVER << 5 | PHARAOH      << 2 | EAST,
  SILVER_PHARAOH_SOUTH      = SILVER << 5 | PHARAOH      << 2 | SOUTH,
  SILVER_PHARAOH_WEST       = SILVER << 5 | PHARAOH      << 2 | WEST,
  SILVER_PYRAMID_NORTH      = SILVER << 5 | PYRAMID      << 2 | NORTH,
  SILVER_PYRAMID_EAST       = SILVER << 5 | PYRAMID      << 2 | EAST,
  SILVER_PYRAMID_SOUTH      = SILVER << 5 | PYRAMID      << 2 | SOUTH,
  SILVER_PYRAMID_WEST       = SILVER << 5 | PYRAMID      << 2 | WEST,
  SILVER_SCARAB_NORTH       = SILVER << 5 | SCARAB       << 2 | NORTH,
  SILVER_SCARAB_EAST        = SILVER << 5 | SCARAB       << 2 | EAST,
  SILVER_SCARAB_SOUTH       = SILVER << 5 | SCARAB       << 2 | SOUTH,
  SILVER_SCARAB_WEST        = SILVER << 5 | SCARAB       << 2 | WEST,
  SILVER_SPHINX_NORTH       = SILVER << 5 | SPHINX       << 2 | NORTH,
  SILVER_SPHINX_EAST        = SILVER << 5 | SPHINX       << 2 | EAST,
  SILVER_SPHINX_SOUTH       = SILVER << 5 | SPHINX       << 2 | SOUTH,
  SILVER_SPHINX_WEST        = SILVER << 5 | SPHINX       << 2 | WEST,
  RED_ANUBIS_NORTH          = RED    << 5 | ANUBIS       << 2 | NORTH,
  RED_ANUBIS_EAST           = RED    << 5 | ANUBIS       << 2 | EAST,
  RED_ANUBIS_SOUTH          = RED    << 5 | ANUBIS       << 2 | SOUTH,
  RED_ANUBIS_WEST           = RED    << 5 | ANUBIS       << 2 | WEST,
  RED_EYE_OF_HORUS_NORTH    = RED    << 5 | EYE_OF_HORUS << 2 | NORTH,
  RED_EYE_OF_HORUS_EAST     = RED    << 5 | EYE_OF_HORUS << 2 | EAST,
  RED_EYE_OF_HORUS_SOUTH    = RED    << 5 | EYE_OF_HORUS << 2 | SOUTH,
  RED_EYE_OF_HORUS_WEST     = RED    << 5 | EYE_OF_HORUS << 2 | WEST,
  RED_PHARAOH_NORTH         = RED    << 5 | PHARAOH      << 2 | NORTH,
  RED_PHARAOH_EAST          = RED    << 5 | PHARAOH      << 2 | EAST,
  RED_PHARAOH_SOUTH         = RED    << 5 | PHARAOH      << 2 | SOUTH,
  RED_PHARAOH_WEST          = RED    << 5 | PHARAOH      << 2 | WEST,
  RED_PYRAMID_NORTH         = RED    << 5 | PYRAMID      << 2 | NORTH,
  RED_PYRAMID_EAST          = RED    << 5 | PYRAMID      << 2 | EAST,
  RED_PYRAMID_SOUTH         = RED    << 5 | PYRAMID      << 2 | SOUTH,
  RED_PYRAMID_WEST          = RED    << 5 | PYRAMID      << 2 | WEST,
  RED_SCARAB_NORTH          = RED    << 5 | SCARAB       << 2 | NORTH,
  RED_SCARAB_EAST           = RED    << 5 | SCARAB       << 2 | EAST,
  RED_SCARAB_SOUTH          = RED    << 5 | SCARAB       << 2 | SOUTH,
  RED_SCARAB_WEST           = RED    << 5 | SCARAB       << 2 | WEST,
  RED_SPHINX_NORTH          = RED    << 5 | SPHINX       << 2 | NORTH,
  RED_SPHINX_EAST           = RED    << 5 | SPHINX       << 2 | EAST,
  RED_SPHINX_SOUTH          = RED    << 5 | SPHINX       << 2 | SOUTH,
  RED_SPHINX_WEST           = RED    << 5 | SPHINX       << 2 | WEST,
};

enum Rotation : unsigned int {
  POSITIVE,
  NEGATIVE
};

inline Color colorOf(Piece p) {
  assert(p != NO_PIECE);
  return Color((p & COLOR_MASK) >> 5);
}

constexpr Direction operator~(Direction d) {
  return Direction(d ^ SOUTH);
}

inline Direction directionOf(Piece p) {
  assert(p != NO_PIECE);
  return Direction(p & WEST);
}

inline Direction reflect(Piece p, Direction d) {
  assert(p & REFLECTOR_MASK);
  return Direction(p & 1 ? d ^ EAST : d ^ WEST);
}

constexpr Piece make(Color c, PieceType pt, Direction d) {
  return Piece(c << 5 | pt << 2 | d);
}

constexpr PieceType typeOf(Piece p) {
  return PieceType((p & PIECE_MASK) >> 2);
}

constexpr Piece rotatePos(Piece p) {
  return Piece((p & WEST) == WEST ? p - 3 : p + 1);
}

constexpr Piece rotateNeg(Piece p) {
  return Piece((p & WEST) == NORTH ? p + 3 : p - 1);
}

constexpr Piece flip(Piece p) {
  return Piece(p ^ WEST);
}

#endif
