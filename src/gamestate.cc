#include "gamestate.h"

namespace khet {

Gamestate::Gamestate(Layout layout=CLASSIC) {
}

void Gamestate::initLayout(Layout layout) {
  switch (layout) {
  case CLASSIC:
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
    break;
  case IMHOTEP:
    red_ = initBitboard(std::vector<Square> {
      A4, A5, A8, E8, F4, F5, F8, G3, G6, G8, H8, I4, I5
    });
    silver_ = initBitboard(std::vector<Square> {
      B4, B5, C1, D1, D3, D6, E1, E4, E5, F1, J1, J4, J5
    });
    north_ = initBitboard(std::vector<Square> {
      A5, D1, E1, F1, G6, I4, J1
    });
    east_ = initBitboard(std::vector<Square> {
      A4, E5, F5, G3, H8, I5
    });
    south_ = initBitboard(std::vector<Square> {
      A8, B5, D3, E8, F8, G8, J4
    });
    west_ = initBitboard(std::vector<Square> {
      B4, C1, D6, E4, F4, J5
    });
    anubis_ = initBitboard(std::vector<Square> {
      D1, E8, F1, G8
    });
    pharaoh_ = initBitboard(std::vector<Square> {
      E1, F8
    });
    pyramid_ = initBitboard(std::vector<Square> {
      A4, A5, B4, B5, D3, D6, E5, F4, G3, G6, I4, I5, J4, J5
    });
    scarab_ = initBitboard(std::vector<Square> {
      C1, E4, F5, H8
    });
    break;
  case DYNASTY:
    red_ = initBitboard(std::vector<Square> {
      A5, A6, A8, C5, D4, E6, E8, F4, F6, F7, F8, G6, G8
    });
    silver_ = initBitboard(std::vector<Square> {
      D1, D3, E1, E2, E3, E5, F1, F3, G5, H4, J1, J3, J4
    });
    north_ = initBitboard(std::vector<Square> {
      A6, E1, E2, E3, F1, F3, H4, J1
    });
    east_ = initBitboard(std::vector<Square> {
      A5, D3, F4, G5, G8
    });
    south_ = initBitboard(std::vector<Square> {
      A8, C5, E6, E8, F6, F7, F8, J3
    });
    west_ = initBitboard(std::vector<Square> {
      D1, D4, E5, G6, J4
    });
    anubis_ = initBitboard(std::vector<Square> {
      E1, E3, F6, F8
    });
    pharaoh_ = initBitboard(std::vector<Square> {
      E2, F7
    });
    pyramid_ = initBitboard(std::vector<Square> {
      A5, A6, D1, D4, E5, E6, E8, F1, F3, F4, G5, G8, J3, J4
    });
    scarab_ = initBitboard(std::vector<Square> {
      C5, D3, G6, H4
    });
    break;
  }
  // All configurations have the same sphinx placement
  sphinx_ = initBitboard(std::vector<Square> {
    A8, J1
  });
}
