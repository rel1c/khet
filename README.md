# Khet

## Requirements

* CMake 3.19.7
* GNU Make 4.3
* g++ (GCC) 10.3.1

## Setup

To build the main Khet program and testing suite run the `init.sh` script in
the root directory. To undo and clean-up, simply remove the created `build/`
directory.

## Goal

The following is a structure to guide further development. I only look at this
project once in a while, and I could use all the help I can get. The primary
goal is to develop a program that executes a game of Khet 2.0 and employs a
challenging AI agent.

To build an efficient engine I am borrowing from the chess AI playbook and
using bit-boards to hold game state and execute game logic. The situation for
Khet is not as serendipitous as it is for chess. In chess there are 64 squares
on the board which conveniently can be represented by a 64-bit word. Khet has
80 squares with 4 possible directions for each piece. To keep things somewhat
simple I am using 128-bit words to store the state and will be relying on the
extra "unneeded" bits to help with hash collisions (I'm planning on using
[Zobrist](https://en.wikipedia.org/wiki/Zobrist_hashing) hashing unless 
something better comes my way).

For the 128-bit bit-boards I am using the
[bitset](https://www.cplusplus.com/reference/bitset/bitset/) class from the
C++ standard library. It may turn out that an array of 128 bools is faster, but
it's arguably larger given the word size of each bool. This becomes an issue
when storing trees of game states in memory. In the previous implementation
it was not uncommon to encounter 1000-depth decision trees. That was likely
excessive, but nonetheless memory should be spared where it can.

The goal of this project does not include a nice graphical representation of
the game, but I am entertained by the prospect. Rather I would like to serve
an API such that a GUI could take advantage of the engine, be it 2D, 3D or in
the terminal.

## Notes

### PKN (Peterson Khet Notation)

Similar to the Forsyth-Edwards Notation (FEN) in chess, I have devised my own
notation to describe a Khet position. It is a one-line ASCII string that
encapsulates all the necessary information needed to play a game from a
particular position, minus history for threefold repetition.

A PKN record contains 4 fields, delimited by a space.
1. Piece placement from A1 to J8, where uppercase letters denote silver 
   pieces and lowercase denote red pieces. A series of blank spaces is given by 
   a digit, where 0 represents 10 spaces. A forward slash `/` signifies
   the end of a row. Pieces are represented as such, Anubis='A', pharaoh='R',
   pyramid='P', scarab='S' and sphinx='X'.
2. Piece rotation, in order of placed pieces. Directions are represented by only
   lowercase letters, one for each cardinal direction, 'n', 'e', 's' and 'w'.
2. The color of the active player.
3. The current turn, incremented after the Red player makes a move.

For example, here is the PKN for the starting configuration of the Classic game
arrangement.

```
2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1s1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0
```
