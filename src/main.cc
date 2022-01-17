#include <iostream>
#include "piece.h"
#include "board.h"

int main(int argc, const char **argv) {
  std::cout << "NO_PIECE: " << std::bitset<7>(NO_PIECE) << std::endl;
  std::cout << "SILVER_NORTH_ANUBIS: " << std::bitset<7>(SILVER_NORTH_ANUBIS) << std::endl;
  std::cout << "SILVER_EAST_ANUBIS: " << std::bitset<7>(SILVER_EAST_ANUBIS) << std::endl;
  std::cout << "SILVER_SOUTH_ANUBIS: " << std::bitset<7>(SILVER_SOUTH_ANUBIS) << std::endl;
  std::cout << "SILVER_WEST_ANUBIS: " << std::bitset<7>(SILVER_WEST_ANUBIS) << std::endl;
  std::cout << "SILVER_NORTH_EYE_OF_HORUS: " << std::bitset<7>(SILVER_NORTH_EYE_OF_HORUS) << std::endl;
  std::cout << "SILVER_EAST_EYE_OF_HORUS: " << std::bitset<7>(SILVER_EAST_EYE_OF_HORUS) << std::endl;
  std::cout << "SILVER_SOUTH_EYE_OF_HORUS: " << std::bitset<7>(SILVER_SOUTH_EYE_OF_HORUS) << std::endl;
  std::cout << "SILVER_WEST_EYE_OF_HORUS: " << std::bitset<7>(SILVER_WEST_EYE_OF_HORUS) << std::endl;
  std::cout << "SILVER_NORTH_PHARAOH: " << std::bitset<7>(SILVER_NORTH_PHARAOH) << std::endl;
  std::cout << "SILVER_EAST_PHARAOH: " << std::bitset<7>(SILVER_EAST_PHARAOH) << std::endl;
  std::cout << "SILVER_SOUTH_PHARAOH: " << std::bitset<7>(SILVER_SOUTH_PHARAOH) << std::endl;
  std::cout << "SILVER_WEST_PHARAOH: " << std::bitset<7>(SILVER_WEST_PHARAOH) << std::endl;
  std::cout << "SILVER_NORTH_PYRAMID: " << std::bitset<7>(SILVER_NORTH_PYRAMID) << std::endl;
  std::cout << "SILVER_EAST_PYRAMID: " << std::bitset<7>(SILVER_EAST_PYRAMID) << std::endl;
  std::cout << "SILVER_SOUTH_PYRAMID: " << std::bitset<7>(SILVER_SOUTH_PYRAMID) << std::endl;
  std::cout << "SILVER_WEST_PYRAMID: " << std::bitset<7>(SILVER_WEST_PYRAMID) << std::endl;
  std::cout << "SILVER_NORTH_SCARAB: " << std::bitset<7>(SILVER_NORTH_SCARAB) << std::endl;
  std::cout << "SILVER_EAST_SCARAB: " << std::bitset<7>(SILVER_EAST_SCARAB) << std::endl;
  std::cout << "SILVER_SOUTH_SCARAB: " << std::bitset<7>(SILVER_SOUTH_SCARAB) << std::endl;
  std::cout << "SILVER_WEST_SCARAB: " << std::bitset<7>(SILVER_WEST_SCARAB) << std::endl;
  std::cout << "SILVER_NORTH_SPHINX: " << std::bitset<7>(SILVER_NORTH_SPHINX) << std::endl;
  std::cout << "SILVER_EAST_SPHINX: " << std::bitset<7>(SILVER_EAST_SPHINX) << std::endl;
  std::cout << "SILVER_SOUTH_SPHINX: " << std::bitset<7>(SILVER_SOUTH_SPHINX) << std::endl;
  std::cout << "SILVER_WEST_SPHINX: " << std::bitset<7>(SILVER_WEST_SPHINX) << std::endl;
  std::cout << "RED_NORTH_ANUBIS: " << std::bitset<7>(RED_NORTH_ANUBIS) << std::endl;
  std::cout << "RED_EAST_ANUBIS: " << std::bitset<7>(RED_EAST_ANUBIS) << std::endl;
  std::cout << "RED_SOUTH_ANUBIS: " << std::bitset<7>(RED_SOUTH_ANUBIS) << std::endl;
  std::cout << "RED_WEST_ANUBIS: " << std::bitset<7>(RED_WEST_ANUBIS) << std::endl;
  std::cout << "RED_NORTH_EYE_OF_HORUS: " << std::bitset<7>(RED_NORTH_EYE_OF_HORUS) << std::endl;
  std::cout << "RED_EAST_EYE_OF_HORUS: " << std::bitset<7>(RED_EAST_EYE_OF_HORUS) << std::endl;
  std::cout << "RED_SOUTH_EYE_OF_HORUS: " << std::bitset<7>(RED_SOUTH_EYE_OF_HORUS) << std::endl;
  std::cout << "RED_WEST_EYE_OF_HORUS: " << std::bitset<7>(RED_WEST_EYE_OF_HORUS) << std::endl;
  std::cout << "RED_NORTH_PHARAOH: " << std::bitset<7>(RED_NORTH_PHARAOH) << std::endl;
  std::cout << "RED_EAST_PHARAOH: " << std::bitset<7>(RED_EAST_PHARAOH) << std::endl;
  std::cout << "RED_SOUTH_PHARAOH: " << std::bitset<7>(RED_SOUTH_PHARAOH) << std::endl;
  std::cout << "RED_WEST_PHARAOH: " << std::bitset<7>(RED_WEST_PHARAOH) << std::endl;
  std::cout << "RED_NORTH_PYRAMID: " << std::bitset<7>(RED_NORTH_PYRAMID) << std::endl;
  std::cout << "RED_EAST_PYRAMID: " << std::bitset<7>(RED_EAST_PYRAMID) << std::endl;
  std::cout << "RED_SOUTH_PYRAMID: " << std::bitset<7>(RED_SOUTH_PYRAMID) << std::endl;
  std::cout << "RED_WEST_PYRAMID: " << std::bitset<7>(RED_WEST_PYRAMID) << std::endl;
  std::cout << "RED_NORTH_SCARAB: " << std::bitset<7>(RED_NORTH_SCARAB) << std::endl;
  std::cout << "RED_EAST_SCARAB: " << std::bitset<7>(RED_EAST_SCARAB) << std::endl;
  std::cout << "RED_SOUTH_SCARAB: " << std::bitset<7>(RED_SOUTH_SCARAB) << std::endl;
  std::cout << "RED_WEST_SCARAB: " << std::bitset<7>(RED_WEST_SCARAB) << std::endl;
  std::cout << "RED_NORTH_SPHINX: " << std::bitset<7>(RED_NORTH_SPHINX) << std::endl;
  std::cout << "RED_EAST_SPHINX: " << std::bitset<7>(RED_EAST_SPHINX) << std::endl;
  std::cout << "RED_SOUTH_SPHINX: " << std::bitset<7>(RED_SOUTH_SPHINX) << std::endl;
  std::cout << "RED_WEST_SPHINX: " << std::bitset<7>(RED_WEST_SPHINX) << std::endl;
  return 0;
}
