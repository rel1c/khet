#include <cassert>

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
  NO_PIECE_TYPE = 0,
  ANUBIS = 1,
  EYE_OF_HORUS = 6,
  PHARAOH = 3,
  PYRAMID = 4,
  SCARAB = 5,
  SPHINX = 2
};

enum Piece : unsigned int {
  NO_PIECE,
  SILVER_NORTH_ANUBIS       = SILVER << 5 | ANUBIS       << 2 | NORTH,
  SILVER_EAST_ANUBIS        = SILVER << 5 | ANUBIS       << 2 | EAST,
  SILVER_SOUTH_ANUBIS       = SILVER << 5 | ANUBIS       << 2 | SOUTH,
  SILVER_WEST_ANUBIS        = SILVER << 5 | ANUBIS       << 2 | WEST,
  SILVER_NORTH_EYE_OF_HORUS = SILVER << 5 | EYE_OF_HORUS << 2 | NORTH,
  SILVER_EAST_EYE_OF_HORUS  = SILVER << 5 | EYE_OF_HORUS << 2 | EAST,
  SILVER_SOUTH_EYE_OF_HORUS = SILVER << 5 | EYE_OF_HORUS << 2 | SOUTH,
  SILVER_WEST_EYE_OF_HORUS  = SILVER << 5 | EYE_OF_HORUS << 2 | WEST,
  SILVER_NORTH_PHARAOH      = SILVER << 5 | PHARAOH      << 2 | NORTH,
  SILVER_EAST_PHARAOH       = SILVER << 5 | PHARAOH      << 2 | EAST,
  SILVER_SOUTH_PHARAOH      = SILVER << 5 | PHARAOH      << 2 | SOUTH,
  SILVER_WEST_PHARAOH       = SILVER << 5 | PHARAOH      << 2 | WEST,
  SILVER_NORTH_PYRAMID      = SILVER << 5 | PYRAMID      << 2 | NORTH,
  SILVER_EAST_PYRAMID       = SILVER << 5 | PYRAMID      << 2 | EAST,
  SILVER_SOUTH_PYRAMID      = SILVER << 5 | PYRAMID      << 2 | SOUTH,
  SILVER_WEST_PYRAMID       = SILVER << 5 | PYRAMID      << 2 | WEST,
  SILVER_NORTH_SCARAB       = SILVER << 5 | SCARAB       << 2 | NORTH,
  SILVER_EAST_SCARAB        = SILVER << 5 | SCARAB       << 2 | EAST,
  SILVER_SOUTH_SCARAB       = SILVER << 5 | SCARAB       << 2 | SOUTH,
  SILVER_WEST_SCARAB        = SILVER << 5 | SCARAB       << 2 | WEST,
  SILVER_NORTH_SPHINX       = SILVER << 5 | SPHINX       << 2 | NORTH,
  SILVER_EAST_SPHINX        = SILVER << 5 | SPHINX       << 2 | EAST,
  SILVER_SOUTH_SPHINX       = SILVER << 5 | SPHINX       << 2 | SOUTH,
  SILVER_WEST_SPHINX        = SILVER << 5 | SPHINX       << 2 | WEST,
  RED_NORTH_ANUBIS          = RED    << 5 | ANUBIS       << 2 | NORTH,
  RED_EAST_ANUBIS           = RED    << 5 | ANUBIS       << 2 | EAST,
  RED_SOUTH_ANUBIS          = RED    << 5 | ANUBIS       << 2 | SOUTH,
  RED_WEST_ANUBIS           = RED    << 5 | ANUBIS       << 2 | WEST,
  RED_NORTH_EYE_OF_HORUS    = RED    << 5 | EYE_OF_HORUS << 2 | NORTH,
  RED_EAST_EYE_OF_HORUS     = RED    << 5 | EYE_OF_HORUS << 2 | EAST,
  RED_SOUTH_EYE_OF_HORUS    = RED    << 5 | EYE_OF_HORUS << 2 | SOUTH,
  RED_WEST_EYE_OF_HORUS     = RED    << 5 | EYE_OF_HORUS << 2 | WEST,
  RED_NORTH_PHARAOH         = RED    << 5 | PHARAOH      << 2 | NORTH,
  RED_EAST_PHARAOH          = RED    << 5 | PHARAOH      << 2 | EAST,
  RED_SOUTH_PHARAOH         = RED    << 5 | PHARAOH      << 2 | SOUTH,
  RED_WEST_PHARAOH          = RED    << 5 | PHARAOH      << 2 | WEST,
  RED_NORTH_PYRAMID         = RED    << 5 | PYRAMID      << 2 | NORTH,
  RED_EAST_PYRAMID          = RED    << 5 | PYRAMID      << 2 | EAST,
  RED_SOUTH_PYRAMID         = RED    << 5 | PYRAMID      << 2 | SOUTH,
  RED_WEST_PYRAMID          = RED    << 5 | PYRAMID      << 2 | WEST,
  RED_NORTH_SCARAB          = RED    << 5 | SCARAB       << 2 | NORTH,
  RED_EAST_SCARAB           = RED    << 5 | SCARAB       << 2 | EAST,
  RED_SOUTH_SCARAB          = RED    << 5 | SCARAB       << 2 | SOUTH,
  RED_WEST_SCARAB           = RED    << 5 | SCARAB       << 2 | WEST,
  RED_NORTH_SPHINX          = RED    << 5 | SPHINX       << 2 | NORTH,
  RED_EAST_SPHINX           = RED    << 5 | SPHINX       << 2 | EAST,
  RED_SOUTH_SPHINX          = RED    << 5 | SPHINX       << 2 | SOUTH,
  RED_WEST_SPHINX           = RED    << 5 | SPHINX       << 2 | WEST,
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
