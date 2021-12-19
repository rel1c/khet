#include "util.h"
#include "move.h"

#include <iostream>
#include <regex>

namespace khet {

Board::Board() {}

Board::Board(Layout layout) {
  setToPkn(layoutToPkn.at(layout));
}

Board::Board(const std::string& pkn) {
  setToPkn(pkn);
}

void Board::setToPkn(const std::string& pkn) {

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
  int i = 0;

  // walk through both piece and direction "stacks"
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

const std::string Board::toPkn() const {
  std::string pieces, directions, player, turn;
  // construct piece and direction sub-strings
  int empty = 0;
  for (auto s : squares) {
    bool is_piece = isPieceAt(s);
    bool end_of_rank = FILE_J[s];
    if (!is_piece) {
      empty++;
    }
    if (is_piece || end_of_rank) {
      if (empty) {
        // account for "0" = "10" in PKN
        int e = (empty == 10) ? 0 : empty;
        pieces += std::to_string(e);
        empty = 0;
      }
      if (is_piece) {
        char piece = charFromPiece(getPieceAt(s));
        piece = (_silver[s]) ? std::toupper(piece) : piece;
        pieces += piece;
        char direction = charFromDirection(getDirectionAt(s));
        directions += direction;
      }
      if (s != J8 && end_of_rank) {
        pieces += '/';
      }
    }
  }
  // combine it all together
  player = charFromColor(_player);
  turn = std::to_string(_turn);
  return pieces + ' ' + directions + ' ' + player + ' ' + turn;
}

bool Board::isLegal() const {
  const Bitboard anubis_red = _anubis & _red;
  const Bitboard pharaoh_red = _pharaoh & _red;
  const Bitboard pyramid_red = _pyramid & _red;
  const Bitboard scarab_red = _scarab & _red;
  const Bitboard sphinx_red = _sphinx & _red;
  const Bitboard anubis_silver = _anubis & _silver;
  const Bitboard pharaoh_silver = _pharaoh & _silver;
  const Bitboard pyramid_silver = _pyramid & _silver;
  const Bitboard scarab_silver = _scarab & _silver;
  const Bitboard sphinx_silver = _sphinx & _silver;
  return (
    (_sphinx[A8] && _red[A8]) &&
    (_sphinx[J1] && _silver[J1]) &&
    (_east[A8] || _south[A8]) &&
    (_north[J1] || _west[J1]) &&
    (!isPieceAt(A1) || _red[A1]) &&
    (!isPieceAt(A2) || _red[A2]) &&
    (!isPieceAt(A3) || _red[A3]) &&
    (!isPieceAt(A4) || _red[A4]) &&
    (!isPieceAt(A5) || _red[A5]) &&
    (!isPieceAt(A6) || _red[A6]) &&
    (!isPieceAt(A7) || _red[A7]) &&
    (!isPieceAt(J2) || _silver[J2]) &&
    (!isPieceAt(J3) || _silver[J3]) &&
    (!isPieceAt(J4) || _silver[J4]) &&
    (!isPieceAt(J5) || _silver[J5]) &&
    (!isPieceAt(J6) || _silver[J6]) &&
    (!isPieceAt(J7) || _silver[J7]) &&
    (!isPieceAt(J8) || _silver[J8]) &&
    (anubis_red.count() <= NUM_ANUBIS) &&
    (pharaoh_red.count() <= NUM_PHARAOH) &&
    (pyramid_red.count() <= NUM_PYRAMID) &&
    (scarab_red.count() <= NUM_SCARAB) &&
    (sphinx_red.count() <= NUM_SPHINX) &&
    (anubis_silver.count() <= NUM_ANUBIS) &&
    (pharaoh_silver.count() <= NUM_PHARAOH) &&
    (pyramid_silver.count() <= NUM_PYRAMID) &&
    (scarab_silver.count() <= NUM_SCARAB) &&
    (sphinx_silver.count() <= NUM_SPHINX)
  );
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
  //TODO could possibly include all boards in the unlikely
  // case that there are missing bits in direction and piece
  // boards
  return (_red | _silver)[s];
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

void Board::doMove(const Move& m) {
  if (!m.isLegal())
    return; //TODO warn!

  if (m.isRotate())
    _rotatePiece(m.from(), m.rotation());
  else if (m.isSwap())
    _swapPieces(m.from(), m.to());
  else
    _movePiece(m.from(), m.to());
}

void Board::undoMove(const Move& m) {
  if (!m.isLegal())
    return; //TODO warn!

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
      char p = '.';
      if (isPieceAt(s)) {
        Color color = getColorAt(s);
        Piece piece = getPieceAt(s);
        p = charFromPiece(piece);
        p = (color == SILVER) ? std::toupper(p) : p;
      }
      std::cout << p;
    }
    std::cout << ' ';
    // output directions
    for (int j = 0; j < NFILES; j++) {
      int n = (i-1) * NFILES + j;
      Square s = static_cast<Square>(n);
      char d = '.';
      if (isPieceAt(s)) {
        Direction direction = getDirectionAt(s);
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

const Bitboard Board::_red_sqrs = initBitboard(
  SquareVec {
    A1, A2, A3, A4, A5, A6, A7, A8, I1, I8
  }
);

const Bitboard Board::_silver_sqrs = initBitboard(
  SquareVec {
    B1, B8, J1, J2, J3, J4, J5, J6, J7, J8
  }
);

const Bitboard Board::_empty = 0;

const Bitboard Board::_full = initBitboard(
  SquareVec {
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
  }
);

bool Board::_verifyPkn(const std::string& pkn) {
  // verify basic layout
  if (pkn.empty())
    return false;
  auto const pkn_regex = std::regex("^[AaPpRrSsXx/0-9]+ [nesw]+ [rs] [0-9]+");
  std::smatch m;
  std::regex_match(pkn, m, pkn_regex);
  if (m.size() > 0)
    return false;

  // verify fields and piece counts
  std::istringstream iss(pkn);
  std::string pieces, directions;
  getline(iss, pieces, ' ');
  getline(iss, directions, ' ');
  if ((std::count(pieces.begin(), pieces.end(), '/') != 7))
    return false;
  unsigned int A, a, P, p, R, r, S, s, X, x;
  A = std::count(pieces.begin(), pieces.end(), 'A');
  a = std::count(pieces.begin(), pieces.end(), 'a');
  P = std::count(pieces.begin(), pieces.end(), 'P');
  p = std::count(pieces.begin(), pieces.end(), 'p');
  R = std::count(pieces.begin(), pieces.end(), 'R');
  r = std::count(pieces.begin(), pieces.end(), 'r');
  S = std::count(pieces.begin(), pieces.end(), 'S');
  s = std::count(pieces.begin(), pieces.end(), 's');
  X = std::count(pieces.begin(), pieces.end(), 'X');
  x = std::count(pieces.begin(), pieces.end(), 'x');

  // check for too many of any piece
  if ((A > NUM_ANUBIS) || (a > NUM_ANUBIS) ||
      (P > NUM_PYRAMID) || (p > NUM_PYRAMID) ||
      (R > NUM_PHARAOH) || (r > NUM_PHARAOH) ||
      (S > NUM_SCARAB) || (s > NUM_SCARAB))
    return false;
  // check for too few pharaohs
  if ((R < NUM_PHARAOH) && (r < NUM_PHARAOH))
    return false;
  // check for wrong number of sphinxes
  if ((X != NUM_SPHINX) || (x != NUM_SPHINX))
    return false;

  // check for correct number of direction symbols
  unsigned int sum = A + a + P + p + R + r + S + s + X + x;
  if (directions.length() != sum)
    return false;

  // check if we missed anything positional
  Board b(pkn);
  return b.isLegal();
}

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

} // namespace khet
