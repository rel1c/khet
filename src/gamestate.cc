#include "gamestate.h"

namespace khet {

Gamestate::Gamestate() {
}

/* For now init the CLASSIC layout and don't parse anything*/
void Gamestate::initLayout() {
  red_ = initBitboard(std::vector<Square> {
    A4, A5, A8, C7, E5, E8, F5, F8, G3, G8, H4, H5, H8,
  }); 
  silver_ = initBitboard(std::vector<Square> {
    C1, C4, C5, D1, D6, E1, E4, F1, F4, H2, J1, J4, J5,
  }); 
  north_ = initBitboard(std::vector<Square> {
    A5, D1, E1, E5, F1, H2, H4, J1
  }); 
  east_ = initBitboard(std::vector<Square> {
    A4, F5, G3, H5, H8
  });
  south_ = initBitboard(std::vector<Square> {
    A8, C5, C7, E8, F4, F8, G8, J4
  }); 
  west_ = initBitboard(std::vector<Square> {
    C1, C4, D6, E4, J5
  }); 
  anubis_ = initBitboard(std::vector<Square> {
    D1, E8, F1, G8
  }); 
  pharaoh_ = initBitboard(std::vector<Square> {
    E1, F8
  }); 
  pyramid_ = initBitboard(std::vector<Square> {
    A4, A5, C1, C4, C5, C7, D6, G3, H2, H4, H5, H8, J4, J5
  }); 
  scarab_ = initBitboard(std::vector<Square> {
    E4, E5, F4, F5
  }); 
  sphinx_ = initBitboard(std::vector<Square> {
    A8, J1
  }); 
}










