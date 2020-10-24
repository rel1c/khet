from const import Color, Constant, Direction, Kind, State
from piece import Anubis, Pharaoh, Pyramid, Scarab, Sphinx

"""
The Game class enforces the rules, not the pieces or the board! If a piece cannot move or
rotate, it is the Game's job to enfore the rules.
"""
class Game(object):

    class Player(object):

        def __init__(self, color):
            self.color = color
            self.pieces = set()

        def give(self, piece):
            self.pieces.add(piece)

        def take(self, piece):
            self.pieces.remove(piece)

    def __init__(self, initial_state=State.CLASSIC):
        self.state = [[None for col in range(Constant.COLS)] for row in range(Constant.ROWS)]
        self.players = (Game.Player(Color.SILVER), Game.Player(Color.RED))
        self.init_game(initial_state)

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

    def fire_laser():
        pass

    def init_game(self, initial_state):
        pieces = {#generalize this!
            Kind.ANUBIS : Anubis,
            Kind.PHARAOH : Pharaoh,
            Kind.PYRAMID : Pyramid,
            Kind.SCARAB : Scarab,
            Kind.SPHINX : Sphinx
        }
        print('Placing game pieces:')
        for token in initial_state:
            color = Color(int(token[0]))
            kind = Kind(int(token[1]))
            direction = Direction(int(token[2]))
            x = int(token[3])
            y = int(token[4])
            piece = pieces[kind](color, direction)
            print('{:<20} @ ({}, {})'.format(str(piece), x, y))
            self.players[color.value].give(piece)
            self.state[x][y] = piece

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
