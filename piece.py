from constants import Color, Direction, Face, Kind


class Piece(object):

    def __init__(self, kind, color, direction=Direction.NORTH):
        self.__kind = kind
        self.__color = color
        self.__direction = direction
        self.__faces = [None] * 4                               # [NORTH, EAST,SOUTH, WEST]

    def getKind(self):
        return self.__kind

    def getColor(self):
        return self.__color

    def getDirection(self):
        return self.__direction

    def getFace(self, laser_direction):
        face_hit = (self.__direction.value + laser_direction.value) % 4    #TODO this is incorrect!
        return self.__faces[face_hit]

    def rotatePositive(self):
        self.__direction = Direction((self.__direction.value + 1) % 4)     # 4 Directions

    def rotateNegative(self):
        self.__direction = Direction((self.__direction.value - 1) % 4)

    def __str__(self):
        raise NotImplementedError('String method not implemented.')


class Scarab(Piece):

    def __init__(self, color):
        Piece.__init__(self, Kind.SCARAB, color)

    def __str__(self):
        return 'Scarab'


class Anubis(Piece):

    def __init__(self, color):
        Piece.__init__(self, Kind.ANUBIS, color)

    def __str__(self):
        return 'Anubis'


class Pyramid(Piece):

    def __init__(self, color):
        Piece.__init__(self, Kind.PYRAMID, color)

    def __str__(self):
        return 'Pyramid'


class Sphinx(Piece):

    def __init__(self, color):
        Piece.__init__(self, Kind.SPHINX, color)

    def __str__(self):
        return 'Sphinx'
