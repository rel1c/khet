# Khet

Version 0.1.0

## Requirements

* CMake 3.19.7
* GNU Make 4.3
* g++ (GCC) 10.3.1

## Setup

To build the main Khet program and testing suite run the `init.sh` script in
the root directory. To undo and clean-up, simply remove the created `build/`
directory.

## Plan

The following is a structure to guide further development. I only look at this
project once in a while, and I could use all the help I can get. The primary
goal is to achieve a state similar to where it was left off, as can be seen in
the old branches using Python and AIMA code from Peter Norvig.

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
(bitset)[https://www.cplusplus.com/reference/bitset/bitset/] class from the
standard library. It may turn out that an array of 128 bools is faster, but
it's arguably larger given the word size of each bool. This becomes an issue
when storing trees of game states in memory. In the previous implementation
it was not uncommon to encounter 1000-depth decision trees. That was likely
excessive, but nonetheless memory should be spared where it can. Bitwise logic
is not that difficult compared to that of arrays, anyway.

The goal of this project does not include a nice graphical representation of
the game, but I am entertained by the prospect. Rather I would like to serve
an API such that a GUI could take advantage of the engine, be it 2D, 3D or in
the terminal. For usability I intend to develop a rudimentary ASCII 
implementation which uses an algebraic notation similar to that of chess.

- [ ] Board configuration
- [ ] Move logic
  - [ ] Scarab piece swap
- [ ] Laser logic
- [ ] Game execution
  - [ ] Output/input with algebraic notation
  - [ ] Scoring
  - [ ] Turn limit option
  - [ ] Enforce repeated state rule
- [ ] Game state tree 
  - [ ] Hash game state
- [ ] AI agent
  - [ ] Min/max algorithm
  - [ ] Alpha/beta pruning
