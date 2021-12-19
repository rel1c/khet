#include "util.h"

namespace khet {

Direction directionFromChar(char ch) {
  Direction d;
  switch (ch) {
  case 'n':
    d = NORTH;
    break;
  case 'e':
    d = EAST;
    break;
  case 's':
    d = SOUTH;
    break;
  case 'w':
    d = WEST;
    break;
  //default:
    //TODO error!
  }
  return d;
}

Piece pieceFromChar(char ch) {
  Piece p;
  switch (ch) {
  case 'a':
  case 'A':
    p = ANUBIS;
    break;
  case 'p':
  case 'P':
    p = PYRAMID;
    break;
  case 'r':
  case 'R':
    p = PHARAOH;
    break;
  case 's':
  case 'S':
    p = SCARAB;
    break;
  case 'x':
  case 'X':
    p = SPHINX;
    break;
  //default:
    //TODO error!
  }
  return p;
}

char charFromColor(Color c) {
  char ch;
  switch (c) {
  case RED:
    ch = 'r';
  case SILVER:
    ch = 's';
  }
  return ch;
}

char charFromDirection(Direction d) {
  char ch;
  switch (d) {
  case NORTH:
    ch = 'n';
    break;
  case EAST:
    ch = 'e';
    break;
  case SOUTH:
    ch = 's';
    break;
  case WEST:
    ch = 'w';
    break;
  }
  return ch;
}

char charFromPiece(Piece p) {
  char ch;
  switch (p) {
  case ANUBIS:
    ch = 'a';
    break;
  case PHARAOH:
    ch = 'r';
    break;
  case PYRAMID:
    ch = 'p';
    break;
  case SCARAB:
    ch = 's';
    break;
  case SPHINX:
    ch = 'x';
    break;
  }
  return ch;
}

} // namespace khet
