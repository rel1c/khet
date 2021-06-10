# Khet

## Pieces

- Anubis
- Pharaoh
- Pyramid
- Scarab
- Sphinx

## Board

The board is made up of 80 tiles, arranged in 8 rows and 10 columns.
Silver plays from the south end of the board, and Red from the north.
The northwest and southeast corners of the board are special squares
where only the Sphinxes are located. Along each flank of the board and
in small areas adjacent are restricted squares that only one color of
pieces can occupy.

```
r s + + + + + + r s
r + + + + + + + + s
r + + + + + + + + s
r + + + + + + + + s
r + + + + + + + + s
r + + + + + + + + s
r + + + + + + + + s
r s + + + + + + r s
```

## Rules

The rules for the game follow the rules released for the physical board
game Khet: The Laser Game 2.0.

1. Set up the pieces in one of the three starting positions given:
   - Classic
   - Dynasty
   - Imhotep

2. Silver moves first. Players alternate turns, with each player
   moving only his/her own pieces. All the pieces, including Pharaohs,
   can be moved.

3. Each player has a Sphinx which contains a laser. It is not a playing
   piece and cannot be eliminated from play. It is located in its
   special corner space. On a player's turn the Sphinx can be rotated
   to point the laser down either the first column or the first row.
   This optional rotation of the Sphinx is done __instead__ of moving
   a piece according to the rules which follow: if a player chooses to
   rotate the Sphinx as his/her turn, it must be rotated before the
   laser is fired.

4. If the player does __not__ rotate his/her Sphinx, then: a turn
   consists of moving any one piece one square in any direction
   (including diagonlly) or of rotating a piece a quarter turn (90
   degrees) in either direction without changing squares. A piece
   cannot be moved and rotated on the same turn or rotated more than
   a quarter twist on one turn.

5. No red piece, including a Scarab, can move into any square
   containing a silver Ankh. No silver piece, including a Scarab,
   can move into any square containing a red Eye of Horus. These
   squares are located along portions of the edges of the board.

6. Except for the Scarab, no piece can move into a square occupied by
   another piece of either color.

7. A Scarab can move into an adjacent square occupied by a Pyramid or
   an Anubis of either color; the Pyramid or Anubis then goes to the
   square from which the Scarab started. In other words, the Scarab
   can swap places with an adjacent Pyramid or Anubis, but not with a
   Pharaoh or another Scarab piece. Neither piece rotates during the
   swap.

8. When a player has moved, by either rotating the Spinx or moving a
   piece, he/she fires their laser. Once completed, no player may undo
   their move and the laser must be fired. Players may not test where
   the beam will go by firing the laser before completing their moves!
   When the laser hits one of the mirrors, it will always make a left
   or right hand turn of 90 degrees. The beam always travels along the
   rows and columns.

9. If the laser beam stops on a non-mirrored surface of a Pyramid that
   piece is removed from the board.

10. If the laser beam stops on the front side of an Anubis piece, the
    Anubis is not removed from the board and the turn is over --this
    piece is impervious to a hit on its front. If the laser beam strikes
    a side or back of an Anubis, that piece is removed from the board.

11. The laser is fired only once at the end of a player's turn. The
    turn is over whether or not a piece is hit.

12. The game ends when a beam illuminates a Pharaoh. The winner is the
    player whose Pharaoh wasn't hit. A player who illuminates his or
    her own Pharaoh is out of luck.

13. If the same board arrangement appears for a third time in the same
    game, i.e., the same pieces of the same colors occupy the same
    squares in the same orientations, the player making the next move
    can declare a draw.

## Implementation

Every piece has a direction, specifically an integer between 0-3 corresponding
to north, east, south, west respectively. Attributes of pieces, namely what happens
when one of their faces is hit by the laser, are static and are qualities in the
pieces themselves. Rotations are purely the change in the north facing vector
for each piece, again a number between 0-3. When a laser hit is resolved all
that is needed is a simple formula to redirect its direction. If a nonreflective
surface is hit the piece is eliminated or the laser is absorbed.

The game board is represented as a 80-element tuple, where each 10 consecutive
elements represent a row of board squares. The first element is the northwest
corner of the board from the perspecive of the silver (first) player. This
representation simplifies discovering legal plays as it cuts down on out-of-bounds
checks.

## Khet Board Mapping

```
Algebraic Notation Mapping
  a8, b8, c8, d8, e8, f8, g8, h8, i8, j8,
  a7, b7, c7, d7, e7, f7, g7, h7, i7, j7,
  a6, b6, c6, d6, e6, f6, g6, h6, i6, j6,
  a5, b5, c5, d5, e5, f5, g5, h5, i5, j5,
  a4, b4, c4, d4, e4, f4, g4, h4, i4, j4,
  a3, b3, c3, d3, e3, f3, g3, h3, i3, j3,
  a2, b2, c2, d2, e2, f2, g2, h2, i2, j2,
  a1, b1, c1, d1, e1, f1, g1, h1, i1, j1,

Coordinate Mapping
  07, 17, 27, 37, 47, 57, 67, 77, 87, 97,
  06, 16, 26, 36, 46, 56, 66, 76, 86, 96,
  05, 15, 25, 35, 45, 55, 65, 75, 85, 95,
  04, 14, 24, 34, 44, 54, 64, 74, 84, 94,
  03, 13, 23, 33, 43, 53, 63, 73, 83, 93,
  02, 12, 22, 32, 42, 52, 62, 72, 82, 92,
  01, 11, 21, 31, 41, 51, 61, 71, 81, 91,
  00, 10, 20, 30, 40, 50, 60, 70, 80, 90,

Bitstring Mapping
  70  71  72  73  74  75  76  77  78  79
  60  61  62  63  64  65  66  67  68  69
  50  51  52  53  54  55  56  57  58  59
  40  41  42  43  44  45  46  47  48  49
  30  31  32  33  34  35  36  37  38  39
  20  21  22  23  24  25  26  27  28  29
  10  11  12  13  14  15  16  17  18  19
  00  01  02  03  04  05  06  07  08  09
```
