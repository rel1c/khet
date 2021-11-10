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
(bitset)[https://www.cplusplus.com/reference/bitset/bitset/] class from the
C++ standard library. It may turn out that an array of 128 bools is faster, but
it's arguably larger given the word size of each bool. This becomes an issue
when storing trees of game states in memory. In the previous implementation
it was not uncommon to encounter 1000-depth decision trees. That was likely
excessive, but nonetheless memory should be spared where it can.

The goal of this project does not include a nice graphical representation of
the game, but I am entertained by the prospect. Rather I would like to serve
an API such that a GUI could take advantage of the engine, be it 2D, 3D or in
the terminal. For usability I intend to develop a rudimentary ASCII 
implementation which uses an algebraic notation similar to that of chess.
