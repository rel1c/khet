from enum import IntEnum

COLS = 10
ROWS = 8
SQUARES = COLS * ROWS
# This is a constant layout for the gameboard. The first index in the tuple is the top-left
# from the point of view of the silver (first) player. The values of each square correspond
# with the Color values below.
BOARD = (2, 1, 0, 0, 0, 0, 0, 0, 2, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         2, 1, 0, 0, 0, 0, 0, 0, 2, 1)

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

# This is a constant for the Classic layout of the game pieces. Each square contains an integer
# where each power of 10 is a 0-4 value corresponding to piece color, kind and direction,
# respectively. This is used as a human friendly way to initiate the game state.
class Layout(object):
    CLASSIC = (242, 000, 000, 000, 202, 212, 202, 221, 000, 000,
               000, 000, 222, 000, 000, 000, 000, 000, 000, 000,
               000, 000, 000, 123, 000, 000, 000, 000, 000, 000,
               220, 000, 122, 000, 230, 231, 000, 221, 000, 123,
               221, 000, 123, 000, 133, 132, 000, 220, 000, 122,
               000, 000, 000, 000, 000, 000, 221, 000, 000, 000,
               000, 000, 000, 000, 000, 000, 000, 120, 000, 000,
               000, 000, 123, 100, 110, 100, 000, 000, 000, 140)

# Object class which embodies a game piece.
class Piece(object):

    # Look-up table for piece facings in order to quickly resolve laser hits.
    FACES = {Kind.ANUBIS: (Face.ABSORB, Face.DESTROY, Face.DESTROY, Face.DESTROY),
             Kind.PHARAOH: (Face.DESTROY, Face.DESTROY, Face.DESTROY, Face.DESTROY),
             Kind.PYRAMID: (Face.REFLECT_NEG, Face.REFLECT_POS, Face.DESTROY, Face.DESTROY),
             Kind.SCARAB: (Face.REFLECT_NEG, Face.REFLECT_POS, Face.REFLECT_NEG, Face.REFLECT_POS),
             Kind.SPHINX: (Face.ABSORB, Face.ABSORB, Face.ABSORB, Face.ABSORB)}

    # Each piece corresponds to the three digit number in a game layout.
    def __init__(self, color, kind, direction):
        self.color = color
        self.kind = kind
        self.direction = direction

    # Resolves a laser hit on a piece via the face look-up table and the laser's direction.
    def resolve_hit(self, laser_direction):
        face_hit = (2 + laser_direction.value - self.direction.value) % 4
        return Piece.FACES[self.kind][face_hit]

    # Rotates piece clockwise.
    def rotate_positive(self):
        self.direction = Direction((self.direction.value + 1) % 4)

    # Rotates piece counter-clockwise.
    def rotate_negative(self):
        self.direction = Direction((self.direction.value - 1) % 4)

    # Flips a piece. This is specifically for the Sphinx laser piece as it cannot rotate
    # like other pieces.
    def flip(self):
        self.direction = Direction(self.direction.value ^ 3)

    def __repr__(self):
        return self.color.name + '_' + self.kind.name + '_' + self.direction.name

# TODO Test or fix this coordinate translation method. It was originally intended to 
# translate row and column input to spaces in the 80-tuple.
def pos(r, c):
    return 10 * r + c

# TODO To be depreciated Game object. Replace this with a Khet(Game) object in accordance
# with the AIMA Game class.
class Game(object):

    def start(self, layout=Layout.CLASSIC):
        state = []
        for square in layout:
            if square:
                color = Color(square // 100)
                kind = Kind((square // 10) % 10)
                direction = Direction(square % 10)
                state.append(Piece(color, kind, direction))
            else:
                state.append(None)
        assert len(state) == SQUARES
        return tuple(state)

    def flip_piece(self, r, c):
        piece = self.state[pos(r, c)]
        piece.flip()

    def move_piece(self, r1, c1, r2, c2):
        piece = self.state[pos(r1, c1)]
        self.state[pos(r1, c1)] = None
        self.state[pos(r2, c2)] = piece

    def remove_piece(self, r, c):
        piece = self.state[pos(r, c)]
        color = piece.color.value
        self.players[color].take(piece)
        self.state[pos(r, c)] = None

    def rotate_piece_positive(self, r, c):
        piece = self.state[pos(r, c)]
        piece.rotate_positive()

    def rotate_piece_negative(self, r, c):
        piece = self.state[pos(r, c)]
        piece.rotate_negative()
    
    def fire_laser(self, player):
        r, c = player.laser
        direction = self.state[pos(r, c)].direction
        while True:
            if direction is Direction.NORTH or direction is Direction.SOUTH:
                x += (direction.value - 1)
            else:
                y += (2 - direction.value)
            if (Constant.ROWS < x or x < 0) or (Constant.COLS < y or y < 0):
                print('Laser out of bounds')
                return
            piece = self.state[pos(r, c)]
            if isinstance(piece, Piece):
                face_hit = piece.resolve_hit(direction)
                if face_hit is Face.DESTROY:
                    print('Destroyed piece:{} at location ({}, {})'.format(str(piece), r, c))
                    self.remove_piece(r, c)
                    return
                elif face_hit is Face.REFLECT_POS: 
                    direction = Direction((direction.value + 1) % 4)
                    print('Laser reflected {} off piece:{} at location ({}, {})'.format(direction,
                        str(piece), r, c))
                elif face_hit is Face.REFLECT_NEG:
                    direction = Direction((direction.value - 1) % 4)
                    print('Laser reflected {} off piece:{} at location ({}, {})'.format(direction,
                        str(piece), r, c))
                else:
                    print('Illuminated piece:{} at location ({}, {})'.format(str(piece), r, c))
                    return
