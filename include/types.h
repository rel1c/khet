#include <bitset>
#include <cassert>

#ifndef TYPES_H_
#define TYPES_H_

enum Square : unsigned int {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1, SQ_I1, SQ_J1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2, SQ_I2, SQ_J2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3, SQ_I3, SQ_J3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4, SQ_I4, SQ_J4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5, SQ_I5, SQ_J5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6, SQ_I6, SQ_J6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7, SQ_I7, SQ_J7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8, SQ_I8, SQ_J8,
  SQ_NONE
};

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
  EYE_OF_HORUS,
  PHARAOH,
  PYRAMID,
  SCARAB,
  SPHINX
};

enum Piece : unsigned int {
  NO_PIECE,
  SILVER_NORTH_ANUBIS       = SILVER << 5 | NORTH << 3 | ANUBIS,
  SILVER_NORTH_EYE_OF_HORUS = SILVER << 5 | NORTH << 3 | EYE_OF_HORUS,
  SILVER_NORTH_PHARAOH      = SILVER << 5 | NORTH << 3 | PHARAOH,
  SILVER_NORTH_PYRAMID      = SILVER << 5 | NORTH << 3 | PYRAMID,
  SILVER_NORTH_SCARAB       = SILVER << 5 | NORTH << 3 | SCARAB,
  SILVER_NORTH_SPHINX       = SILVER << 5 | NORTH << 3 | SPHINX,
  SILVER_EAST_ANUBIS        = SILVER << 5 | EAST  << 3 | ANUBIS,
  SILVER_EAST_EYE_OF_HORUS  = SILVER << 5 | EAST  << 3 | EYE_OF_HORUS,
  SILVER_EAST_PHARAOH       = SILVER << 5 | EAST  << 3 | PHARAOH,
  SILVER_EAST_PYRAMID       = SILVER << 5 | EAST  << 3 | PYRAMID,
  SILVER_EAST_SCARAB        = SILVER << 5 | EAST  << 3 | SCARAB,
  SILVER_EAST_SPHINX        = SILVER << 5 | EAST  << 3 | SPHINX,
  SILVER_SOUTH_ANUBIS       = SILVER << 5 | SOUTH << 3 | ANUBIS,
  SILVER_SOUTH_EYE_OF_HORUS = SILVER << 5 | SOUTH << 3 | EYE_OF_HORUS,
  SILVER_SOUTH_PHARAOH      = SILVER << 5 | SOUTH << 3 | PHARAOH,
  SILVER_SOUTH_PYRAMID      = SILVER << 5 | SOUTH << 3 | PYRAMID,
  SILVER_SOUTH_SCARAB       = SILVER << 5 | SOUTH << 3 | SCARAB,
  SILVER_SOUTH_SPHINX       = SILVER << 5 | SOUTH << 3 | SPHINX,
  SILVER_WEST_ANUBIS        = SILVER << 5 | WEST  << 3 | ANUBIS,
  SILVER_WEST_EYE_OF_HORUS  = SILVER << 5 | WEST  << 3 | EYE_OF_HORUS,
  SILVER_WEST_PHARAOH       = SILVER << 5 | WEST  << 3 | PHARAOH,
  SILVER_WEST_PYRAMID       = SILVER << 5 | WEST  << 3 | PYRAMID,
  SILVER_WEST_SCARAB        = SILVER << 5 | WEST  << 3 | SCARAB,
  SILVER_WEST_SPHINX        = SILVER << 5 | WEST  << 3 | SPHINX,
  RED_NORTH_ANUBIS          = RED    << 5 | NORTH << 3 | ANUBIS,
  RED_NORTH_EYE_OF_HORUS    = RED    << 5 | NORTH << 3 | EYE_OF_HORUS,
  RED_NORTH_PHARAOH         = RED    << 5 | NORTH << 3 | PHARAOH,
  RED_NORTH_PYRAMID         = RED    << 5 | NORTH << 3 | PYRAMID,
  RED_NORTH_SCARAB          = RED    << 5 | NORTH << 3 | SCARAB,
  RED_NORTH_SPHINX          = RED    << 5 | NORTH << 3 | SPHINX,
  RED_EAST_ANUBIS           = RED    << 5 | EAST  << 3 | ANUBIS,
  RED_EAST_EYE_OF_HORUS     = RED    << 5 | EAST  << 3 | EYE_OF_HORUS,
  RED_EAST_PHARAOH          = RED    << 5 | EAST  << 3 | PHARAOH,
  RED_EAST_PYRAMID          = RED    << 5 | EAST  << 3 | PYRAMID,
  RED_EAST_SCARAB           = RED    << 5 | EAST  << 3 | SCARAB,
  RED_EAST_SPHINX           = RED    << 5 | EAST  << 3 | SPHINX,
  RED_SOUTH_ANUBIS          = RED    << 5 | SOUTH << 3 | ANUBIS,
  RED_SOUTH_EYE_OF_HORUS    = RED    << 5 | SOUTH << 3 | EYE_OF_HORUS,
  RED_SOUTH_PHARAOH         = RED    << 5 | SOUTH << 3 | PHARAOH,
  RED_SOUTH_PYRAMID         = RED    << 5 | SOUTH << 3 | PYRAMID,
  RED_SOUTH_SCARAB          = RED    << 5 | SOUTH << 3 | SCARAB,
  RED_SOUTH_SPHINX          = RED    << 5 | SOUTH << 3 | SPHINX,
  RED_WEST_ANUBIS           = RED    << 5 | WEST  << 3 | ANUBIS,
  RED_WEST_EYE_OF_HORUS     = RED    << 5 | WEST  << 3 | EYE_OF_HORUS,
  RED_WEST_PHARAOH          = RED    << 5 | WEST  << 3 | PHARAOH,
  RED_WEST_PYRAMID          = RED    << 5 | WEST  << 3 | PYRAMID,
  RED_WEST_SCARAB           = RED    << 5 | WEST  << 3 | SCARAB,
  RED_WEST_SPHINX           = RED    << 5 | WEST  << 3 | SPHINX,
};

enum Rank : unsigned int {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

enum File : unsigned int {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_I, FILE_J
};

const unsigned int NUM_DIRECTIONS = 4;
const unsigned int NUM_FILES = 10;
const unsigned int NUM_RANKS = 8;
const unsigned int NUM_SQUARES = 80;
const unsigned int MAX_MOVES = 121;

const Square SILVER_SPHINX_SQUARE = SQ_J1;
const Square RED_SPHINX_SQUARE = SQ_A8;

inline Color colorOf(Piece p) {
  assert(p != NO_PIECE);
  return Color((p & 0b1100000) >> 5);
}

inline Direction directionOf(Piece p) {
  assert(p != NO_PIECE);
  return Direction((p & 0b11000) >> 3);
}

constexpr PieceType typeOf(Piece p) {
  return PieceType(p & 0b111);
}

inline Direction rotatePos(Direction d) {
  return Direction((d + 1) % NUM_DIRECTIONS);
}

inline Direction rotateNeg(Direction d) {
  return Direction((d - 1) % NUM_DIRECTIONS);
}

inline Direction flip(Direction d) {
  return Direction(d ^ 3);
}

constexpr File fileOf(Square s) {
  return File(s % 10);
}

constexpr Rank rankOf(Square s) {
  return Rank(s / 10);
}

using Bitboard = std::bitset <NUM_SQUARES>;

#endif
