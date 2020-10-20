from const import Color, Constant, Direction, Kind, State
from piece import Anubis, Pharaoh, Pyramid, Scarab, Sphinx

"""
Move(x1, y1, x2, y2)
    - move a piece from (x1, y1) to (x2, y2)
    - check if move is legal
    - check move consequences (scarab)
    - execute move

pieces [[P1, P2, ..., Pi], ..., [ ..., Pn]]
    - each players active pieces on the board
    - pieces are "idependent" of board as they move on it
    - each piece has location as index on 2D array

hand (P1, P2, ..., Pn)
    - each player has a hand (set) of pieces

The Game class enforces the rules, not the pieces or the board! If a piece cannot move or
rotate, it is the Game's job to enfore the rules.
"""
#TODO Initializing the game state should be responsible for constructing all of the players pieces.
#This will ensure they are all at the correct coordinates and will cut down on code length as well
#as make the game more flexible.
class Game(object):

    class Player(object):

        def __init__(self, color):
            self.color = color
            #self.pieces = (Pharaoh(color), Anubis(color), Anubis(color), Sphinx(color),
            #               Scarab(color), Scarab(color, Pyramid(color), Pyramid(color),
            #               Pyramid(color), Pyramid(color), Pyramid(color), Pyramid(color),
            #               Pyramid(color))
            self.pieces = []

        def assign(self, piece):
            self.pieces.append(piece)

    def __init__(self, initial_state=State.CLASSIC):
        self.state = [[None for col in range(Constant.COLS)] for row in range(Constant.ROWS)]
        self.players = (Game.Player(Color.SILVER), Game.Player(Color.RED))
        self.init_game(initial_state)

    def move_piece():
        pass

    def is_over():
        pass

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
            self.players[color.value].assign(piece)
            self.state[x][y] = piece
