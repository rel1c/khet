from const import Color, Direction, Face, Kind
#TODO eliminate all get/set, use attributes
#TODO consolidate default parameters
#TODO default argument depening on color, or this too complicated?
#TODO combine rotate methods, call Sphinx(rotate) with only one?

class Piece(object):

    FACES_ANUBIS = (Face.ABSORB, Face.DESTROY, Face.DESTROY, Face.DESTROY)
    FACES_PHARAOH = (Face.DESTROY, Face.DESTROY, Face.DESTROY, Face.DESTROY)
    FACES_PYRAMID = (Face.REFLECT_NEG, Face.REFLECT_POS, Face.DESTROY, Face.DESTROY)
    FACES_SCARAB = (Face.REFLECT_NEG, Face.REFLECT_POS, Face.REFLECT_NEG, Face.REFLECT_POS)
    FACES_SPHINX = (Face.ABSORB, Face.ABSORB, Face.ABSORB, Face.ABSORB)

    def __init__(self, kind, color, direction):
        self.color = color
        self.direction = direction
        self.faces = None
        self.kind = kind

    def resolve_hit(self, laser_direction):
        face_hit = (2 - laser_direction.value + self.direction.value) % 4
        print(face_hit)
        return self.faces[face_hit]

    def rotate_positive(self):
        self.direction = Direction((self.direction.value + 1) % 4)

    def rotate_negative(self):
        self.direction = Direction((self.direction.value - 1) % 4)

    def __str__(self):
        return self.color.name + '_' + self.kind.name + '_' + self.direction.name

class Anubis(Piece):

#  ,===,
#  |   |
#  |___|

    def __init__(self, color, direction=Direction.NORTH): 
        Piece.__init__(self, Kind.ANUBIS, color, direction) 
        self.faces = Piece.FACES_ANUBIS

class Pharaoh(Piece):

#  |vvv|
#  |   |
#  |___|

    def __init__(self, color, direction=Direction.NORTH):
        Piece.__init__(self, Kind.PHARAOH, color, direction)
        self.faces = Piece.FACES_PHARAOH

class Pyramid(Piece):

#   |\
#   | \
#   |__\

    def __init__(self, color, direction=Direction.NORTH):
        Piece.__init__(self, Kind.PYRAMID, color, direction)
        self.faces = Piece.FACES_PYRAMID

class Scarab(Piece):

#  \@\
#   \ \
#    \_\

    def __init__(self, color, direction=Direction.NORTH):
        Piece.__init__(self, Kind.SCARAB, color, direction)
        self.faces = Piece.FACES_SCARAB

class Sphinx(Piece):

#   )|(
#  |   |
#  |___|

    def __init__(self, color, direction=Direction.NORTH):
        Piece.__init__(self, Kind.SPHINX, color, direction)
        self.faces = Piece.FACES_SPHINX
