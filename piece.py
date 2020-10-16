from const import Color, Direction, Face, Kind

class Piece(object):

    FACES_ANUBIS = ()
    FACES_PHARAOH = (Face.GAME, Face.GAME, Face.GAME, Face.GAME) 
    FACES_PYRAMID = (Face.REFLECT_NEG, Face.REFLECT_POS, Face.DESTROY, Face.DESTROY)
    FACES_SCARAB = (Face.REFLECT_NEG, Face.REFLECT_POS, Face.REFLECT_NEG, Face.REFLECT_POS)
    FACES_SPHINX= (Face.ABSORB, Face.ABSORB, Face.ABSORB, Face.ABSORB)

    def __init__(self, kind, color, direction=Direction.NORTH):
        self.kind = kind
        self.color = color
        self.direction = direction
        self.faces = [None] * 4
        self.move = True

    def getKind(self):
        return self.kind #TODO eliminate all get/set, use attributes

    def getColor(self):
        return self.color

    def getDirection(self):
        return self.direction

    def getFace(self, laser_direction):
        face_hit = (2 - laser_direction.value + self.direction.value) % 4
        print(face_hit)
        return self.faces[face_hit]

    def rotatePositive(self):
        self.direction = Direction((self.direction.value + 1) % 4)

    def rotateNegative(self):
        self.direction = Direction((self.direction.value - 1) % 4)

    def __str__(self):
        return self.color.name + '_' + self.kind.name + '_' + self.direction.name

class Scarab(Piece):

#  \`\
#   \ \
#    \_\

    def __init__(self, color):
        Piece.__init__(self, Kind.SCARAB, color)
        self.faces = list(Piece.FACES_SCARAB)

class Anubis(Piece):

#  ,===,
#  |   |
#  |___|

    def __init__(self, color):
        Piece.__init__(self, Kind.ANUBIS, color)
        self.faces[0] = Face.ABSORB
        self.faces[1] = Face.DESTROY
        self.faces[2] = Face.DESTROY
        self.faces[3] = Face.DESTROY

class Pharaoh(Piece):

#  |vvv|
#  |   |
#  |___|

    def __init__(self, color):
        Piece.__init__(self, Kind.PHARAOH, color)
        self.faces = list(FACES_PHARAOH)

class Pyramid(Piece):

#   |\
#   | \
#   |__\

    def __init__(self, color):
        Piece.__init__(self, Kind.PYRAMID, color)
        self.faces = list(FACES_PYRAMID)

class Sphinx(Piece):

#   )|(
#  |   |
#  |___|

    def __init__(self, color):
        Piece.__init__(self, Kind.SPHINX, color)
        self.faces = list(FACES_SPHINX)
        self.move = False
