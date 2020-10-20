from enum import Enum

class Color(Enum):
    SILVER = 0
    RED = 1

class Constant(object):
    COLS = 10
    ROWS = 8

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

class Kind(Enum):
    ANUBIS = 0
    PHARAOH = 1
    PYRAMID = 2
    SCARAB = 3
    SPHINX = 4

class State(object):
    CLASSIC = ['14200', '10204', '11205', '10206', '12107', '12212', '02323', '12030', '02232',
               '13034', '13135', '12137', '02339', '12140', '02342', '03344', '03245', '12047',
               '02249', '12156', '02067', '02372', '00073', '01074', '00075', '04079']
