#include "board.h"
#include "util.h"

#include <regex>

namespace khet {

static Direction directionFromChar(char);
static Piece pieceFromChar(char);
static bool verifyPkn(const std::string);

Board::Board() {}

Board::Board(std::string pkn) {
  setToPkn(pkn);
}

Board::Board(Layout layout=CLASSIC) {
  setToPkn(layoutToPkn.at(layout));
}

void Board::setToPkn(std::string pkn) {
  // make sure given string is a valid PKN string
  if (!verifyPkn(pkn))
    return; //TODO error!

  // extract fields
  std::istringstream iss(pkn);
  std::string piece_str, direction_str, player_str, turn_str;
  getline(iss, piece_str, ' ');
  getline(iss, direction_str, ' ');
  getline(iss, player_str, ' ');
  getline(iss, turn_str, ' ');

  // initialize board with values
  Color color;
  Direction direction;
  Piece piece;
  auto p = piece_str.cbegin();
  auto d = direction_str.cbegin();
  unsigned int i = 0;
  while (p != piece_str.cend() && d != direction_str.cend()) {
    if (isdigit(*p)) {
      i += *p - '0';
    }
    else if (*p != '/') {
      color = (isupper(*p)) ? SILVER : RED;
      piece = pieceFromChar(*p);
      direction = directionFromChar(*d);
      Square square = static_cast<Square>(i);
      _addPiece(square, color, direction, piece);
      d++;
    }
    p++;
  }
  _player = (player_str == "r") ? RED : SILVER;
  _turn = std::stoi(turn_str);
}

Bitboard Board::getColor(Color c) const {
  if (c == RED)
    return _red;
  else if (c == SILVER)
    return _silver;
  else
    return _empty;
}

Bitboard Board::getDirection(Direction d) const {
  if (d == NORTH)
    return _north;
  else if (d == EAST)
    return _east;
  else if (d == SOUTH)
    return _south;
  else if (d == WEST)
    return _west;
  else
    return _empty;
}

Bitboard Board::getPiece(Piece p) const {
  if (p == ANUBIS)
    return _anubis;
  else if (p == PHARAOH)
    return _pharaoh;
  else if (p == PYRAMID)
    return _pyramid;
  else if (p == SCARAB)
    return _scarab;
  else if (p == SPHINX)
    return _sphinx;
  else
    return _empty;
}

Color Board::getColorAt(Square s) const {
  Color c;
  if (_red[s])
    c = RED;
  else if (_silver[s])
    c = SILVER;
  return c;
}

Direction Board::getDirectionAt(Square s) const {
  Direction d;
  if (_north[s])
    d = NORTH;
  else if (_east[s])
    d = EAST;
  else if (_south[s])
    d = SOUTH;
  else if (_west[s])
    d = WEST;
  return d;
}

Piece Board::getPieceAt(Square s) const {
  Piece p;
  if (_anubis[s])
    p = ANUBIS;
  else if (_pharaoh[s])
    p = PHARAOH;
  else if (_pyramid[s])
    p = PYRAMID;
  else if (_scarab[s])
    p = SCARAB;
  else if (_sphinx[s])
    p = SPHINX;
  return p;
}

Bitboard Board::getAllPieces() const {
  return _red | _silver;
}

Bitboard Board::getSwappable() const {
  return _anubis | _pyramid;
}

Color Board::getPlayer() const {
  return _player;
}

void Board::doMove(Move) { //TODO
}

const Bitboard Board::_red_sqrs = initBitboard(Squares {
  A1, A2, A3, A4, A5, A6, A7, A8, I1, I8
});

const Bitboard Board::_silver_sqrs = initBitboard(Squares {
  B1, B8, J1, J2, J3, J4, J5, J6, J7, J8
});

const Bitboard Board::_empty = 0;

const Bitboard Board::_full = initBitboard(Squares {
  A1, A2, A3, A4, A5, A6, A7, A8,
  B1, B2, B3, B4, B5, B6, B7, B8,
  C1, C2, C3, C4, C5, C6, C7, C8,
  D1, D2, D3, D4, D5, D6, D7, D8,
  E1, E2, E3, E4, E5, E6, E7, E8,
  F1, F2, F3, F4, F5, F6, F7, F8,
  G1, G2, G3, G4, G5, G6, G7, G8,
  H1, H2, H3, H4, H5, H6, H7, H8,
  I1, I2, I3, I4, I5, I6, I7, I8,
  J1, J2, J3, J4, J5, J6, J7, J8,
});

const Bitboard Board::_sphinx = initBitboard(Squares {
  A8, J1
});

static Direction directionFromChar(char ch) {
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
  }
  return d;
}

static Piece pieceFromChar(char ch) {
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
  }
  return p;
}

static bool verifyPkn(const std::string pkn) {
  if (pkn.empty())
    return false;
  auto const pkn_regex = std::regex("[AaPpRrRSsXx/0-9]+ [nesw]+ [rs] [0-9]+");
  std::smatch m;
  if (std::regex_match(pkn, m, pkn_regex) == false)
    return false;
  // TODO check number of each character and length boundaries
  return true;
}

} // namespace khet
