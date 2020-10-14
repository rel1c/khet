from kind import Kind
from color import Color


class Piece(object):

    def __init__(self, kind, color):
        self.__kind = kind
        self.__color = color
    
    def getKind(self):
        return self.__kind

    def getColor(self):
        return self.__color

    def __repr__(self):
        return 'Piece:' + self.__kind.name + ':' + self.__color.name

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


class EyeOfHorus(Piece):
    def __init__(self, color):
        Piece.__init__(self, Kind.EYE_OF_HORUS, color)

    def __str__(self):
        return 'Eye Of Horus'
