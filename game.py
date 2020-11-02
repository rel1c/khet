from const import Color, Constant, Direction, Face, Kind, State
from piece import Piece

"""
The Game class enforces the rules, not the pieces or the board! If a piece cannot move or
rotate, it is the Game's job to enfore the rules.
"""
class Game(object):

    class Player(object):

        def __init__(self, color):
            self.color = color
            self.laser = None
            self.pieces = set()

        def give(self, piece):
            self.pieces.add(piece)

        def take(self, piece):
            self.pieces.remove(piece)

    def __init__(self, initial_state=State.CLASSIC):
        self.state = [[None for col in range(Constant.COLS)] for row in range(Constant.ROWS)]
        self.players = (Game.Player(Color.SILVER), Game.Player(Color.RED))
        self.init_game(initial_state)

    def flip_piece(self, x, y):
        piece = self.state[x][y]
        piece.flip()
        print('Flipped piece:{} at location ({}, {})'.format(str(piece), x, y))

    def move_piece(self, x1, y1, x2, y2):
        piece = self.state[x1][y1]
        self.state[x1][y1] = None
        self.state[x2][y2] = piece
        print('Moved piece:{} from location ({}, {}) to ({}, {})'.format(str(piece), x1, y1, x2, y2))

    def remove_piece(self, x, y):
        piece = self.state[x][y]
        color = piece.color.value
        self.players[color].take(piece)
        self.state[x][y] = None
        print('Removed piece:{} at location ({}, {})'.format(str(piece), x, y))

    def rotate_piece_positive(self, x, y):
        piece = self.state[x][y]
        piece.rotate_positive()
        print('Rotated piece:{} at location ({}, {})'.format(str(piece), x, y))

    def rotate_piece_negative(self, x, y):
        piece = self.state[x][y]
        piece.rotate_negative()
        print('Rotated piece:{} at location ({}, {})'.format(str(piece), x, y))

    def fire_laser(self, player):
        x, y = player.laser
        direction = self.state[x][y].direction
        while True:
            if direction is Direction.NORTH or direction is Direction.SOUTH:
                x += (direction.value - 1)
            else:
                y += (2 - direction.value)
            print('x:{} y:{}'.format(x, y))
            if (Constant.ROWS < x or x < 0) or (Constant.COLS < y or y < 0):
                print('Laser out of bounds')
                return
            piece = self.state[x][y]
            if isinstance(piece, Piece):
                face_hit = piece.resolve_hit(direction)
                if face_hit is Face.DESTROY:
                    print('Destroyed piece:{} at location ({}, {})'.format(str(piece), x, y))
                    return
                elif face_hit is Face.REFLECT_POS: 
                    direction = Direction((direction.value + 1) % 4)
                    print('Laser reflected {} off piece:{} at location ({}, {})'.format(direction,
                        str(piece), x, y))
                elif face_hit is Face.REFLECT_NEG:
                    direction = Direction((direction.value - 1) % 4)
                    print('Laser reflected {} off piece:{} at location ({}, {})'.format(direction,
                        str(piece), x, y))
                else:
                    print('Illuminated piece:{} at location ({}, {})'.format(str(piece), x, y))
                    return

    def init_game(self, initial_state):
        print('Placing game pieces:')
        for token in initial_state:
            color = Color(int(token[0]))
            kind = Kind(int(token[1]))
            direction = Direction(int(token[2]))
            player = self.players[color.value]
            x = int(token[3])
            y = int(token[4])
            piece = Piece(color, kind, direction)
            print('{:<20} @ ({}, {})'.format(str(piece), x, y))
            player.give(piece)
            self.state[x][y] = piece
            if piece.kind is Kind.SPHINX:
                player.laser = (x,y)

    def __str__(self):
        s = ""
        for x in range(Constant.ROWS):
            for y in range(Constant.COLS):
                piece = self.state[x][y]
                if piece is None:
                    ch = ' + '
                else:
                    ch = str(piece.color.value)
                    ch += str(piece.kind.value)
                    ch += str(piece.direction.value)
                s += ch + ' '
            s += '\n'
        return s
