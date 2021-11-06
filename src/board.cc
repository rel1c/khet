#include "board.h"

namespace khet {

Bitboard Bitboard::getSquaresRed() {
  return empty_;
}

Bitboard Bitboard::getSquaresSilver() {
  return empty_;
}

Bitboard Bitboard::getRed() {
  return empty_;
}

Bitboard Bitboard::getSilver() {
  return empty_;
}

Bitboard Bitboard::getNorth() {
  return empty_;
}

Bitboard Bitboard::getEast() {
  return empty_;
}

Bitboard Bitboard::getSouth() {
  return empty_;
}

Bitboard Bitboard::getWest() {
  return empty_;
}

Bitboard Bitboard::getAnubis() {
  return empty_;
}

Bitboard Bitboard::getRedAnubis() {
  return empty_;
}

Bitboard Bitboard::getSilverAnubis() {
  return empty_;
}

Bitboard Bitboard::getAnubisNorth() {
  return empty_;
}

Bitboard Bitboard::getAnubisEast() {
  return empty_;
}

Bitboard Bitboard::getAnubisSouth() {
  return empty_;
}

Bitboard Bitboard::getAnubisWest() {
  return empty_;
}

Bitboard Bitboard::getRedAnubisNorth() {
  return empty_;
}

Bitboard Bitboard::getRedAnubisEast() {
  return empty_;
}

Bitboard Bitboard::getRedAnubisSouth() {
  return empty_;
}

Bitboard Bitboard::getRedAnubisWest() {
  return empty_;
}

Bitboard Bitboard::getSilverAnubisNorth() {
  return empty_;
}

Bitboard Bitboard::getSilverAnubisEast() {
  return empty_;
}

Bitboard Bitboard::getSilverAnubisSouth() {
  return empty_;
}

Bitboard Bitboard::getSilverAnubisWest() {
  return empty_;
}

Bitboard Bitboard::getPharaoh() {
  return empty_;
}

Bitboard Bitboard::getRedPharaoh() {
  return empty_;
}

Bitboard Bitboard::getSilverPharaoh() {
  return empty_;
}

Bitboard Bitboard::getPharaohNorth() {
  return empty_;
}

Bitboard Bitboard::getPharaohEast() {
  return empty_;
}

Bitboard Bitboard::getPharaohSouth() {
  return empty_;
}

Bitboard Bitboard::getPharaohWest() {
  return empty_;
}

Bitboard Bitboard::getRedPharaohNorth() {
  return empty_;
}

Bitboard Bitboard::getRedPharaohEast() {
  return empty_;
}

Bitboard Bitboard::getRedPharaohSouth() {
  return empty_;
}

Bitboard Bitboard::getRedPharaohWest() {
  return empty_;
}

Bitboard Bitboard::getSilverPharaohNorth() {
  return empty_;
}

Bitboard Bitboard::getSilverPharaohEast() {
  return empty_;
}

Bitboard Bitboard::getSilverPharaohSouth() {
  return empty_;
}

Bitboard Bitboard::getSilverPharaohWest() {
  return empty_;
}

Bitboard Bitboard::getPyramid() {
  return empty_;
}

Bitboard Bitboard::getRedPyramid() {
  return empty_;
}

Bitboard Bitboard::getSilverPyramid() {
  return empty_;
}

Bitboard Bitboard::getPyramidNorth() {
  return empty_;
}

Bitboard Bitboard::getPyramidEast() {
  return empty_;
}

Bitboard Bitboard::getPyramidSouth() {
  return empty_;
}

Bitboard Bitboard::getPyramidWest() {
  return empty_;
}

Bitboard Bitboard::getRedPyramidNorth() {
  return empty_;
}

Bitboard Bitboard::getRedPyramidEast() {
  return empty_;
}

Bitboard Bitboard::getRedPyramidSouth() {
  return empty_;
}

Bitboard Bitboard::getRedPyramidWest() {
  return empty_;
}

Bitboard Bitboard::getSilverPyramidNorth() {
  return empty_;
}

Bitboard Bitboard::getSilverPyramidEast() {
  return empty_;
}

Bitboard Bitboard::getSilverPyramidSouth() {
  return empty_;
}

Bitboard Bitboard::getSilverPyramidWest() {
  return empty_;
}

Bitboard Bitboard::getScarab() {
  return empty_;
}

Bitboard Bitboard::getRedScarab() {
  return empty_;
}

Bitboard Bitboard::getSilverScarab() {
  return empty_;
}

Bitboard Bitboard::getScarabNorth() {
  return empty_;
}

Bitboard Bitboard::getScarabEast() {
  return empty_;
}

Bitboard Bitboard::getScarabSouth() {
  return empty_;
}

Bitboard Bitboard::getScarabWest() {
  return empty_;
}

Bitboard Bitboard::getRedScarabNorth() {
  return empty_;
}

Bitboard Bitboard::getRedScarabEast() {
  return empty_;
}

Bitboard Bitboard::getRedScarabSouth() {
  return empty_;
}

Bitboard Bitboard::getRedScarabWest() {
  return empty_;
}

Bitboard Bitboard::getSilverScarabNorth() {
  return empty_;
}

Bitboard Bitboard::getSilverScarabEast() {
  return empty_;
}

Bitboard Bitboard::getSilverScarabSouth() {
  return empty_;
}

Bitboard Bitboard::getSilverScarabWest() {
  return empty_;
}

Bitboard Bitboard::getSphinx() {
  return empty_;
}

Bitboard Bitboard::getRedSphinx() {
  return empty_;
}

Bitboard Bitboard::getSilverSphinx() {
  return empty_;
}

Bitboard Bitboard::getSphinxNorth() {
  return empty_;
}

Bitboard Bitboard::getSphinxEast() {
  return empty_;
}

Bitboard Bitboard::getSphinxSouth() {
  return empty_;
}

Bitboard Bitboard::getSphinxWest() {
  return empty_;
}

Bitboard Bitboard::getRedSphinxNorth() {
  return empty_;
}

Bitboard Bitboard::getRedSphinxEast() {
  return empty_;
}

Bitboard Bitboard::getRedSphinxSouth() {
  return empty_;
}

Bitboard Bitboard::getRedSphinxWest() {
  return empty_;
}

Bitboard Bitboard::getSilverSphinxNorth() {
  return empty_;
}

Bitboard Bitboard::getSilverSphinxEast() {
  return empty_;
}

Bitboard Bitboard::getSilverSphinxSouth() {
  return empty_;
}

Bitboard Bitboard::getSilverSphinxWest() {
  return empty_;
}

Board::bb_squares_red = initBitboard(
  std::vector<int> {A1, A2, A3, A4, A5, A6, A7, A8, I1, I8}
);

Board::bb_squares_silver = initBitboard(
  std::vector<int> {B1, B8, J1, J2, J3, J4, J5, J6, J7, J8}
);

} // namespace khet
