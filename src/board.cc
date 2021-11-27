#include "board.h"

namespace khet {

Board::Board() {}

Board::Board(Layout layout=CLASSIC) {
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

const std::array<Bitboard, NFILES * NRANKS> Board::moves_ = {
  initBitboard(std::vector<Square> {A2, B1, B2}),                     // A1
  initBitboard(std::vector<Square> {A1, A2, B2, C1, C2}),             // B1
  initBitboard(std::vector<Square> {B1, B2, C2, D1, D2}),             // C1
  initBitboard(std::vector<Square> {C1, C2, D2, E1, E2}),             // D1
  initBitboard(std::vector<Square> {D1, D2, E2, F1, F2}),             // E1
  initBitboard(std::vector<Square> {E1, E2, F2, G1, G2}),             // F1
  initBitboard(std::vector<Square> {F1, F2, G2, H1, H2}),             // G1
  initBitboard(std::vector<Square> {G1, G2, H2, I1, I2}),             // H1
  initBitboard(std::vector<Square> {H1, H2, I2, J1, J2}),             // I1
  initBitboard(std::vector<Square> {I1, I2, J2}),                     // J1

  initBitboard(std::vector<Square> {A1, A3, B1, B2, B3}),             // A2
  initBitboard(std::vector<Square> {A1, A2, A3, B1, B3, C1, C2, C3}), // B2
  initBitboard(std::vector<Square> {B1, B2, B3, C1, C3, D1, D2, D3}), // C2
  initBitboard(std::vector<Square> {C1, C2, C3, D1, D3, E1, E2, E3}), // D2
  initBitboard(std::vector<Square> {D1, D2, D3, E1, E3, F1, F2, F3}), // E2
  initBitboard(std::vector<Square> {E1, E2, E3, F1, F3, G1, G2, G3}), // F2
  initBitboard(std::vector<Square> {F1, F2, F3, G1, G3, H1, H2, H3}), // G2
  initBitboard(std::vector<Square> {G1, G2, G3, H1, H3, I1, I2, I3}), // H2
  initBitboard(std::vector<Square> {H1, H2, H3, I1, I3, J1, J2, J3}), // I2
  initBitboard(std::vector<Square> {I1, I2, I3, J1, J3}),             // J2

  initBitboard(std::vector<Square> {A2, A4, B2, B3, B4}),             // A3
  initBitboard(std::vector<Square> {A2, A3, A4, B2, B4, C2, C3, C4}), // B3
  initBitboard(std::vector<Square> {B2, B3, B4, C2, C4, D2, D3, D4}), // C3
  initBitboard(std::vector<Square> {C2, C3, C4, D2, D4, E2, E3, E4}), // D3
  initBitboard(std::vector<Square> {D2, D3, D4, E2, E4, F2, F3, F4}), // E3
  initBitboard(std::vector<Square> {E2, E3, E4, F2, F4, G2, G3, G4}), // F3
  initBitboard(std::vector<Square> {F2, F3, F4, G2, G4, H2, H3, H4}), // G3
  initBitboard(std::vector<Square> {G2, G3, G4, H2, H4, I2, I3, I4}), // H3
  initBitboard(std::vector<Square> {H2, H3, H4, I2, I4, J2, J3, J4}), // I3
  initBitboard(std::vector<Square> {I2, I3, I4, J2, J4}),             // J3

  initBitboard(std::vector<Square> {A3, A5, B3, B4, B5}),             // A4
  initBitboard(std::vector<Square> {A3, A4, A5, B3, B5, C3, C4, C5}), // B4
  initBitboard(std::vector<Square> {B3, B4, B5, C3, C5, D3, D4, D5}), // C4
  initBitboard(std::vector<Square> {C3, C4, C5, D3, D5, E3, E4, E5}), // D4
  initBitboard(std::vector<Square> {D3, D4, D5, E3, E5, F3, F4, F5}), // E4
  initBitboard(std::vector<Square> {E3, E4, E5, F3, F5, G3, G4, G5}), // F4
  initBitboard(std::vector<Square> {F3, F4, F5, G3, G5, H3, H4, H5}), // G4
  initBitboard(std::vector<Square> {G3, G4, G5, H3, H5, I3, I4, I5}), // H4
  initBitboard(std::vector<Square> {H3, H4, H5, I3, I5, J3, J4, J5}), // I4
  initBitboard(std::vector<Square> {I3, I4, I5, J3, J5}),             // J4

  initBitboard(std::vector<Square> {A4, A6, B4, B5, B6}),             // A5
  initBitboard(std::vector<Square> {A4, A5, A6, B4, B6, C4, C5, C6}), // B5
  initBitboard(std::vector<Square> {B4, B5, B6, C4, C6, D4, D5, D6}), // C5
  initBitboard(std::vector<Square> {C4, C5, C6, D4, D6, E4, E5, E6}), // D5
  initBitboard(std::vector<Square> {D4, D5, D6, E4, E6, F4, F5, F6}), // E5
  initBitboard(std::vector<Square> {E4, E5, E6, F4, F6, G4, G5, G6}), // F5
  initBitboard(std::vector<Square> {F4, F5, F6, G4, G6, H4, H5, H6}), // G5
  initBitboard(std::vector<Square> {G4, G5, G6, H4, H6, I4, I5, I6}), // H5
  initBitboard(std::vector<Square> {H4, H5, H6, I4, I6, J4, J5, J6}), // I5
  initBitboard(std::vector<Square> {I4, I5, I6, J4, J6}),             // J5

  initBitboard(std::vector<Square> {A5, A7, B5, B6, B7}),             // A6
  initBitboard(std::vector<Square> {A5, A6, A7, B5, B7, C5, C6, C7}), // B6
  initBitboard(std::vector<Square> {B5, B6, B7, C5, C7, D5, D6, D7}), // C6
  initBitboard(std::vector<Square> {C5, C6, C7, D5, D7, E5, E6, E7}), // D6
  initBitboard(std::vector<Square> {D5, D6, D7, E5, E7, F5, F6, F7}), // E6
  initBitboard(std::vector<Square> {E5, E6, E7, F5, F7, G5, G6, G7}), // F6
  initBitboard(std::vector<Square> {F5, F6, F7, G5, G7, H5, H6, H7}), // G6
  initBitboard(std::vector<Square> {G5, G6, G7, H5, H7, I5, I6, I7}), // H6
  initBitboard(std::vector<Square> {H5, H6, H7, I5, I7, J5, J6, J7}), // I6
  initBitboard(std::vector<Square> {I5, I6, I7, J5, J7}),             // J6

  initBitboard(std::vector<Square> {A6, A8, B6, B7, B8}),             // A7
  initBitboard(std::vector<Square> {A6, A7, A8, B6, B8, C6, C7, C8}), // B7
  initBitboard(std::vector<Square> {B6, B7, B8, C6, C8, D6, D7, D8}), // C7
  initBitboard(std::vector<Square> {C6, C7, C8, D6, D8, E6, E7, E8}), // D7
  initBitboard(std::vector<Square> {D6, D7, D8, E6, E8, F6, F7, F8}), // E7
  initBitboard(std::vector<Square> {E6, E7, E8, F6, F8, G6, G7, G8}), // F7
  initBitboard(std::vector<Square> {F6, F7, F8, G6, G8, H6, H7, H8}), // G7
  initBitboard(std::vector<Square> {G6, G7, G8, H6, H8, I6, I7, I8}), // H7
  initBitboard(std::vector<Square> {H6, H7, H8, I6, I8, J6, J7, J8}), // I7
  initBitboard(std::vector<Square> {I6, I7, I8, J6, J8}),             // J7

  initBitboard(std::vector<Square> {A7, B7, B8}),                     // A8
  initBitboard(std::vector<Square> {A7, A8, B7, C7, C8}),             // B8
  initBitboard(std::vector<Square> {B7, B8, C7, D7, D8}),             // C8
  initBitboard(std::vector<Square> {C7, C8, D7, E7, E8}),             // D8
  initBitboard(std::vector<Square> {D7, D8, E7, F7, F8}),             // E8
  initBitboard(std::vector<Square> {E7, E8, F7, G7, G8}),             // F8
  initBitboard(std::vector<Square> {F7, F8, G7, H7, H8}),             // G8
  initBitboard(std::vector<Square> {G7, G8, H7, I7, I8}),             // H8
  initBitboard(std::vector<Square> {H7, H8, I7, J7, J8}),             // I8
  initBitboard(std::vector<Square> {I7, I8, J7}),                     // J8
};

const Bitboard Board::squares_red_ = initBitboard(std::vector<Square> {
  A1, A2, A3, A4, A5, A6, A7, A8, I1, I8
});

const Bitboard Board::squares_silver_ = initBitboard(std::vector<Square> {
  B1, B8, J1, J2, J3, J4, J5, J6, J7, J8
});

const Bitboard Board::empty_ = 0;

const Bitboard Board::full_ = initBitboard(std::vector<Square> {
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

} // namespace khet
