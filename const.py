from enum import Enum

class Color(Enum):
    SILVER = 0
    RED = 1

class Direction(Enum):
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

class Face(Enum):
    REFLECT_POS = 0
    REFLECT_NEG = 1
    ABSORB = 2
    DESTROY = 3
    GAME = 4

class Kind(Enum):
    ANUBIS = 0
    PHARAOH = 1
    PYRAMID = 2
    SCARAB = 3
    SPHINX = 4
