#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

namespace khet {

class Board {
public:
  Bitboard getMoves(const Square) const;

  Bitboard getSquaresRed();
  Bitboard getSquaresSilver();
  Bitboard getRed();
  Bitboard getSilver();
                     
  Bitboard getNorth();
  Bitboard getEast();
  Bitboard getSouth();
  Bitboard getWest();
                     
  Bitboard getAnubis();
  Bitboard getRedAnubis();
  Bitboard getSilverAnubis();
  Bitboard getAnubisNorth();
  Bitboard getAnubisEast();
  Bitboard getAnubisSouth();
  Bitboard getAnubisWest();
  Bitboard getRedAnubisNorth();
  Bitboard getRedAnubisEast();
  Bitboard getRedAnubisSouth();
  Bitboard getRedAnubisWest();
  Bitboard getSilverAnubisNorth();
  Bitboard getSilverAnubisEast();
  Bitboard getSilverAnubisSouth();
  Bitboard getSilverAnubisWest();
                     
  Bitboard getPharaoh();
  Bitboard getRedPharaoh();
  Bitboard getSilverPharaoh();
  Bitboard getPharaohNorth();
  Bitboard getPharaohEast();
  Bitboard getPharaohSouth();
  Bitboard getPharaohWest();
  Bitboard getRedPharaohNorth();
  Bitboard getRedPharaohEast();
  Bitboard getRedPharaohSouth();
  Bitboard getRedPharaohWest();
  Bitboard getSilverPharaohNorth();
  Bitboard getSilverPharaohEast();
  Bitboard getSilverPharaohSouth();
  Bitboard getSilverPharaohWest();
                     
  Bitboard getPyramid();
  Bitboard getRedPyramid();
  Bitboard getSilverPyramid();
  Bitboard getPyramidNorth();
  Bitboard getPyramidEast();
  Bitboard getPyramidSouth();
  Bitboard getPyramidWest();
  Bitboard getRedPyramidNorth();
  Bitboard getRedPyramidEast();
  Bitboard getRedPyramidSouth();
  Bitboard getRedPyramidWest();
  Bitboard getSilverPyramidNorth();
  Bitboard getSilverPyramidEast();
  Bitboard getSilverPyramidSouth();
  Bitboard getSilverPyramidWest();
                     
  Bitboard getScarab();
  Bitboard getRedScarab();
  Bitboard getSilverScarab();
  Bitboard getScarabNorth();
  Bitboard getScarabEast();
  Bitboard getScarabSouth();
  Bitboard getScarabWest();
  Bitboard getRedScarabNorth();
  Bitboard getRedScarabEast();
  Bitboard getRedScarabSouth();
  Bitboard getRedScarabWest();
  Bitboard getSilverScarabNorth();
  Bitboard getSilverScarabEast();
  Bitboard getSilverScarabSouth();
  Bitboard getSilverScarabWest();
                     
  Bitboard getSphinx();
  Bitboard getRedSphinx();
  Bitboard getSilverSphinx();
  Bitboard getSphinxNorth();
  Bitboard getSphinxEast();
  Bitboard getSphinxSouth();
  Bitboard getSphinxWest();
  Bitboard getRedSphinxNorth();
  Bitboard getRedSphinxEast();
  Bitboard getRedSphinxSouth();
  Bitboard getRedSphinxWest();
  Bitboard getSilverSphinxNorth();
  Bitboard getSilverSphinxEast();
  Bitboard getSilverSphinxSouth();
  Bitboard getSilverSphinxWest();
private:
  static const std::vector<Bitboard> moves_;

  static const Bitboard squares_red_;
  static const Bitboard squares_silver_;

  static const Bitboard empty_;
  static const Bitboard full_;

  Bitboard red_;
  Bitboard silver_;

  Bitboard north_;
  Bitboard east_;
  Bitboard south_;
  Bitboard west_;

  Bitboard anubis_;
  Bitboard pharaoh_;
  Bitboard pyramid_;
  Bitboard scarab_;
  Bitboard sphinx_;
};

} // namespace khet

#endif
