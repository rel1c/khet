#include "board.h"
#include "util.h"

#include <iostream>
#include <regex>

namespace khet {

static Direction directionFromChar(char);
static Piece pieceFromChar(char);
static char charFromDirection(Direction d);
static char charFromPiece(Piece p);
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
      if (*p == '0')
        i += 10;
      else
        i += *p - '0';
    }
    else if (*p != '/') {
      color = (isupper(*p)) ? SILVER : RED;
      piece = pieceFromChar(*p);
      direction = directionFromChar(*d);
      Square square = static_cast<Square>(i++);
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
  else
    return _silver;
}

Bitboard Board::getDirection(Direction d) const {
  if (d == NORTH)
    return _north;
  else if (d == EAST)
    return _east;
  else if (d == SOUTH)
    return _south;
  else
    return _west;
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
  else
    return _sphinx;
}

bool Board::isPieceAt(Square s) const {
  return (_red | _silver)[s] == 1;
}

Color Board::getColorAt(Square s) const {
  Color c;
  if (_red[s])
    c = RED;
  else
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
  else
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
  else
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

void Board::doMove(Move m) {
  if (!m.isLegal())
    return; //TODO error!

  if (m.isRotate())
    _rotatePiece(m.from(), m.rotation());
  else if (m.isSwap())
    _swapPieces(m.from(), m.to());
  else
    _movePiece(m.from(), m.to());
}

void Board::undoMove(Move m) {
  if (!m.isLegal())
    return; //TODO error!

  if (m.isRotate()) {
    Rotation inverse = static_cast<Rotation>(m.rotation() * -1);
    _rotatePiece(m.from(), inverse);
  }
  else if (m.isSwap())
    _swapPieces(m.to(), m.from());
  else
    _movePiece(m.to(), m.from());
}

/**
 * 8 x...arap.. s...ssse.. SILVER
 * 7 ..p....... ..s....... [0]
 * 6 ...P...... ...w......
 * 5 p.P.ss.p.P n.s.ne.e.w
 * 4 p.P.SS.p.P e.w.ws.n.s
 * 3 ......p... ......e...
 * 2 .......P.. .......n..
 * 1 ..PARA...X ..wnnn...n
 *   abcdefghij abcdefghij
 */
void Board::display() const {
  for (int i = NRANKS; i > 0; i--) {
    std::cout << i << ' ';
    // output pieces, capitalized according to color
    for (int j = 0; j < NFILES; j++) {
      int n = (i-1) * NFILES + j;
      Square s = static_cast<Square>(n);
      Color color = getColorAt(s);
      Piece piece = getPieceAt(s);
      char p = '.';
      if (isPieceAt(s)) {
        p = charFromPiece(piece);
        if (color == SILVER)
          p = std::toupper(p);
      }
      std::cout << p;
    }
    std::cout << ' ';
    // output directions
    for (int j = 0; j < NFILES; j++) {
      int n = (i-1) * NFILES + j;
      Square s = static_cast<Square>(n);
      Direction direction = getDirectionAt(s);
      char d = '.';
      if (isPieceAt(s)) {
        d = charFromDirection(direction);
      }
      std::cout << d;
    }
    if (i == NRANKS)
      std::cout << " " << colorStrings[_player];
    else if (i == NRANKS - 1)
      std::cout << " turn: " << _turn;
    std::cout << "\n";
  }
  std::cout << "  abcdefghij abcdefghij" << std::endl;
}

const Bitboard Board::_red_sqrs = initBitboard(SquareVec {
  A1, A2, A3, A4, A5, A6, A7, A8, I1, I8
});

const Bitboard Board::_silver_sqrs = initBitboard(SquareVec {
  B1, B8, J1, J2, J3, J4, J5, J6, J7, J8
});

const Bitboard Board::_empty = 0;

const Bitboard Board::_full = initBitboard(SquareVec {
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

void Board::_addPiece(Square s, Color c, Direction d, Piece p) {
  Bitboard sqr = SQUARES[s];
  Bitboard& color = _getColorRef(c);
  Bitboard& direction = _getDirectionRef(d);
  Bitboard& piece = _getPieceRef(p);
  color |= sqr;
  direction |= sqr;
  piece |= sqr;
}

void Board::_movePiece(Square from, Square to) {
  Bitboard sqr_from = SQUARES[from];
  Bitboard sqr_to = SQUARES[to];

  Bitboard& color = _getColorRefAt(from);
  Bitboard& direction = _getDirectionRefAt(from);
  Bitboard& piece = _getPieceRefAt(from);

  color &= ~sqr_from;
  direction &= ~sqr_from;
  piece &= ~sqr_from;

  color |= sqr_to;
  direction |= sqr_to;
  piece |= sqr_to;
}

void Board::_swapPieces(Square from, Square to) {
  Bitboard sqr_from = SQUARES[from];
  Bitboard sqr_to = SQUARES[to];

  Bitboard& color_from = _getColorRefAt(from);
  Bitboard& direction_from = _getDirectionRefAt(from);
  Bitboard& piece_from = _getPieceRefAt(from);

  Bitboard& color_to = _getColorRefAt(to);
  Bitboard& direction_to = _getDirectionRefAt(to);
  Bitboard& piece_to = _getPieceRefAt(to);

  color_from = color_from & ~sqr_from | sqr_to;
  direction_from = direction_from  & ~sqr_from | sqr_to;
  piece_from = piece_from & ~sqr_from | sqr_to;

  color_to = color_to & ~sqr_to | sqr_from;
  direction_to = direction_to & ~sqr_to | sqr_from;
  piece_to = piece_to & ~sqr_to | sqr_from;
}

void Board::_rotatePiece(Square s, Rotation r) {
  Bitboard sqr = SQUARES[s];
  Direction d_from = getDirectionAt(s);
  Direction d_to = static_cast<Direction>((d_from + r) % 4);
  Bitboard& direction_from = _getDirectionRef(d_from);
  Bitboard& direction_to = _getDirectionRef(d_to);
  direction_from &= ~sqr;
  direction_to |= sqr;
}

void Board::_removePiece(Square s) {
  Bitboard sqr = SQUARES[s];
  Bitboard& color = _getColorRefAt(s);
  Bitboard& direction = _getDirectionRefAt(s);
  Bitboard& piece = _getPieceRefAt(s);
  color &= ~sqr;
  direction &= ~sqr;
  piece &= ~sqr;
}

Bitboard& Board::_getColorRef(Color c) {
  if (c == RED)
    return _red;
  else
    return _silver;
}

Bitboard& Board::_getDirectionRef(Direction d) {
  if (d == NORTH)
    return _north;
  else if (d == EAST)
    return _east;
  else if (d == SOUTH)
    return _south;
  else
    return _west;
}

Bitboard& Board::_getPieceRef(Piece p) {
  if (p == ANUBIS)
    return _anubis;
  else if (p == PHARAOH)
    return _pharaoh;
  else if (p == PYRAMID)
    return _pyramid;
  else if (p == SCARAB)
    return _scarab;
  else
    return _sphinx;
}

Bitboard& Board::_getColorRefAt(Square s) {
  if (_red[s])
    return _red;
  else
    return _silver;
}

Bitboard& Board::_getDirectionRefAt(Square s) {
  if (_north[s])
    return _north;
  else if (_east[s])
    return _east;
  else if (_south[s])
    return _south;
  else
    return _west;
}

Bitboard& Board::_getPieceRefAt(Square s) {
  if (_anubis[s])
    return _anubis;
  else if (_pharaoh[s])
    return _pharaoh;
  else if (_pyramid[s])
    return _pyramid;
  else if (_scarab[s])
    return _scarab;
  else
    return _sphinx;
}

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
  //default:
    //TODO error!
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
  //default:
    //TODO error!
  }
  return p;
}

static char charFromDirection(Direction d) {
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
  default:
    ch = '\0';
  }
  return ch;
}

static char charFromPiece(Piece p) {
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
  default:
    ch = '\0';
  }
  return ch;
}

static bool verifyPkn(const std::string pkn) {
  if (pkn.empty())
    return false;
  auto const pkn_regex = std::regex("^[AaPpRrRSsXx/0-9]+ [nesw]+ [rs] [0-9]+");
  std::smatch m;
  std::regex_match(pkn, m, pkn_regex);
  // insert debugging here based on value of m
  return m.size() > 0;
}

} // namespace khet
