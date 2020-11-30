import numpy as np
from collections import namedtuple
from enum import IntEnum

# ______________________________________________________________________________
# Khet constant, enum, and helper class definitions

# The number of repeated, indentical board layouts in a game that result in a draw
DRAW_CONDITION = 3    

# Board size                            
NUM_SQUARES = (ROWS := 8)  * (COLS := 10)

# Constant layout for the gameboard. 
# The values of each square correspond with the Color values below.
SQUARES = [[2, 1, 0, 0, 0, 0, 0, 0, 2, 1], 
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 1, 0, 0, 0, 0, 0, 0, 2, 1]]

# Classifiers to differentiate between the type of player moves 
Move = namedtuple('Move', 'cur_sq, new_sq')
Rotate = namedtuple('Rotate', 'cur_sq, val')
Swap = namedtuple('Swap', 'cur_sq, new_sq')

# Player colors, starting at 1 to avoid the confusion of the sequence '000' in game layout.
class Color(IntEnum):
  SILVER = 1
  RED = 2

# Cardinal directions for piece facing and laser routing.
class Direction(IntEnum):
  NORTH = 0
  EAST = 1
  SOUTH = 2
  WEST = 3

# Faces of game pieces represented by the action to take upon being hit by the laser.
class Face(IntEnum):
  REFLECT_POS = 0
  REFLECT_NEG = 1
  ABSORB = 2
  DESTROY = 3

# Game pieces, listed alphabetically.
class Kind(IntEnum):
  ANUBIS = 0
  PHARAOH = 1
  PYRAMID = 2
  SCARAB = 3
  SPHINX = 4

# Rotation values correspond to clockwise, flipping and counter-clockwise
class Rotation(IntEnum):
  NEG = -1
  FLIP = 0
  POS = 1

# This is a constant for the Classic layout of the game pieces. Each square contains an integer
# where each power of 10 is a 0-4 value corresponding to piece color, kind and direction,
# respectively. This is used as a human friendly way to initiate the game state.
class Layout(object):
    CLASSIC = [[242, 000, 000, 000, 202, 212, 202, 221, 000, 000],
               [000, 000, 222, 000, 000, 000, 000, 000, 000, 000],
               [000, 000, 000, 123, 000, 000, 000, 000, 000, 000],
               [220, 000, 122, 000, 230, 231, 000, 221, 000, 123],
               [221, 000, 123, 000, 133, 132, 000, 220, 000, 122],
               [000, 000, 000, 000, 000, 000, 221, 000, 000, 000],
               [000, 000, 000, 000, 000, 000, 000, 120, 000, 000],
               [000, 000, 123, 100, 110, 100, 000, 000, 000, 140]]


# ______________________________________________________________________________
# Monte Carlo Tree Search helper class and function
class MCT_Node:
  """Node in the Monte Carlo search tree, keeps track of the children states."""

  def __init__(self, parent=None, state=None, U=0, N=0):
      self.__dict__.update(parent=parent, state=state, U=U, N=N)
      self.children = {}
      self.actions = None


def ucb(n, C=1.4):
      return np.inf if n.N == 0 else n.U / n.N + C * np.sqrt(np.log(n.parent.N) / n.N)