from const import Color, Direction, Face, Kind

class Piece(object):

    FACES = {Kind.ANUBIS:(Face.ABSORB, Face.DESTROY, Face.DESTROY, Face.DESTROY),
             Kind.PHARAOH:(Face.DESTROY, Face.DESTROY, Face.DESTROY, Face.DESTROY),
             Kind.PYRAMID:(Face.REFLECT_NEG, Face.REFLECT_POS, Face.DESTROY, Face.DESTROY),
             Kind.SCARAB:(Face.REFLECT_NEG, Face.REFLECT_POS, Face.REFLECT_NEG, Face.REFLECT_POS),
             Kind.SPHINX:(Face.ABSORB, Face.ABSORB, Face.ABSORB, Face.ABSORB)}

    def __init__(self, color, kind, direction):
        self.color = color
        self.kind = kind
        self.direction = direction

    def resolve_hit(self, laser_direction):
        face_hit = (2 + laser_direction.value - self.direction.value) % 4
        return Piece.FACES[self.kind][face_hit]

    def rotate_positive(self):
        self.direction = Direction((self.direction.value + 1) % 4)

    def rotate_negative(self):
        self.direction = Direction((self.direction.value - 1) % 4)

    def flip(self):
        self.direction = Direction(self.direction.value ^ 3)

    def __str__(self):
        return self.color.name + '_' + self.kind.name + '_' + self.direction.name
