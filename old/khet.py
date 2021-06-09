import copy
from collections import namedtuple
from enum import IntEnum
from game import Game, GameState

Move = namedtuple('Move', 'cur_sq, new_sq')
Rotate = namedtuple('Rotate', 'cur_sq, val')
Swap = namedtuple('Swap', 'cur_sq, new_sq')

COLS = 10
ROWS = 8
NUM_SQUARES = COLS * ROWS

# This is a constant layout for the gameboard. 
# The values of each square correspond with the Color values below.
SQUARES = [[2, 1, 0, 0, 0, 0, 0, 0, 2, 1], 
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 0, 0, 0, 0, 0, 0, 0, 0, 1],
           [2, 1, 0, 0, 0, 0, 0, 0, 2, 1]]


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

# Rotation values correspond to clockwise, flipping and counter-clockwise
class Rotation(IntEnum):
    NEG = -1
    FLIP = 0
    POS = 1

# This is a constant for the Classic layout of the game pieces. Each square contains an integer
# where each power of 10 is a 0-4 value corresponding to piece color, kind and direction,
# respectively. This is used as a human friendly way to initiate the game state.
class Layout(object):
    CLASSIC = [[242, 000, 000, 000, 202, 212, 202, 221, 000, 000],
               [000, 000, 222, 000, 000, 000, 000, 000, 000, 000],
               [000, 000, 000, 123, 000, 000, 000, 000, 000, 000],
               [220, 000, 122, 000, 230, 231, 000, 221, 000, 123],
               [221, 000, 123, 000, 133, 132, 000, 220, 000, 122],
               [000, 000, 000, 000, 000, 000, 221, 000, 000, 000],
               [000, 000, 000, 000, 000, 000, 000, 120, 000, 000],
               [000, 000, 123, 100, 110, 100, 000, 000, 000, 140]]


# Object class which embodies a game piece.
class Piece(object):

    # Look-up table to generate the faces of a piece
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
        self.faces = Piece.FACES[kind]

    # Resolves a laser hit on a piece via the face look-up table and the laser's direction.
    def resolve_hit(self, laser_direction):
        hit = (2 + laser_direction.value - self.direction.value) % 4
        return self.faces[hit]

    # Rotates a piece clockwise or counter-clockwise, or flips it #
    def rotate(self, rotation):
        assert -1 <= rotation <= 1
        if not rotation: #then flip
            self.direction = Direction(self.direction.value ^ 3)
        else:
            self.direction = Direction((self.direction.value + rotation) % 4)

    # Return numerical values of piece in string for displaying game state #
    def values(self):
        return "{}{}{}".format(self.color, self.kind, self.direction)

    def __repr__(self):
        return "{}_{}_{}".format(self.color.name, self.kind.name, self.direction.name)


class Khet(Game):

    # Relative row/col offsets from a given square for moving N, NE, E, SE, S, SW, W, NW
    ordinals = [(-1,0), (-1,1), (0,1), (1,1), (1,0), (1,-1), (0, -1), (-1, -1)]

    # Determine if a square is on the game board #
    @staticmethod
    def in_bounds(row, col):
        return 0 <= row < ROWS and 0 <= col < COLS

    # Return the color of the opposing player #
    @staticmethod
    def opponent_color(player_color):
        return player_color % 2 + 1  # Color enum begins at 1 instead of 0

    # Construct 2D Piece object array from provided layout #
    def __init__(self, layout=Layout.CLASSIC):
        initial_board = [[None] * COLS for i in range(ROWS)]
        self.lasers = {Color.SILVER: (), Color.RED: ()} # The sphinx locations for each player

        for i, row in enumerate(layout):
            for j, square in enumerate(row):
                if square:
                    # square is a three digit number indicating the color, kind, and direction of a piece
                    color = Color(square // 100)
                    kind = Kind((square // 10) % 10)
                    direction = Direction(square % 10)
                    initial_board[i][j] = Piece(color, kind, direction)
                    if kind == Kind.SPHINX:
                        self.lasers[color] = (i, j)

        
        self.initial = GameState(to_move=Color.SILVER, utility=0, board=initial_board, moves=[])


    # Return all of a player's legal moves #
    def actions(self, state):
        for i, row in enumerate(state.board):
            for j, _ in enumerate(row):
                self.get_legal_moves(state, (i, j))
        return state.moves


    # Modify the game board according to the selected move #
    def result(self, state, action):
        board = copy.deepcopy(state.board)
        i, j = action.cur_sq

        if isinstance(action, Move):
            new_i, new_j = action.new_sq
            board[new_i][new_j] = board[i][j]
            board[i][j] = None      
        elif isinstance(action, Rotate):
            board[i][j].rotate(action.val.value) #TODO ugly but it works
        else:
            # action is Swap
            new_i, new_j = action.new_sq
            board[i][j], board[new_i][new_j] = board[new_i][new_j], board[i][j]
            
        self.fire_laser(board, self.lasers[state.to_move])

        return GameState(to_move=self.opponent_color(state.to_move),
                         utility=self.compute_utility(board, action, state.to_move), #TODO: implement compute_utility
                         board=board, moves=[])


    # Retrieve utility of game state #
    def utility(self, state, player):
        pass #TODO: implement


    # Determine if game has come to an end #
    def terminal_test(self, state):
        pass #TODO: implement


    # Display game state in human readable format #
    def display(self, state):
        board = state.board
        for i, row in enumerate(board):
            for j, _ in enumerate(row):
                square = board[i][j]
                if square:
                    print(square.values(), end=' ')
                else:
                    print("---", end=' ')
            print()


    # Compute utility of game state #
    def compute_utility(self, board, move, player):
        pass #TODO: implement


    # Find all legal moves for a piece #
    def get_legal_moves(self, state, square):
        row, col = square
        piece = state.board[row][col]

        if piece is None or piece.color != state.to_move:
            # There is no piece at the current square or the piece belongs to the opponent
            # and therefore cannot have any legal moves for the player
            return
        if piece.kind == Kind.SPHINX:
            # Only possible move for Sphinx is to flip rotation
            state.moves.append(Rotate(cur_sq=square, val=Rotation.FLIP))
            return

        # Iterate over the relative indices of the 8 surrounding squares to check movement/swap possibilities
        for row_offset, col_offset in Khet.ordinals:    
            new_row = row + row_offset
            new_col = col + col_offset
            if self.in_bounds(new_row, new_col) and SQUARES[new_row][new_col] != self.opponent_color(state.to_move):
                # Square is both on the board and not the opponent's color
                if (adj_piece := state.board[new_row][new_col]) is not None:
                    # Adjacent square has a piece
                    if piece.kind == Kind.SCARAB and adj_piece.kind == Kind.PYRAMID or adj_piece.kind == Kind.ANUBIS:
                        # Requirements for Scarab swap are satisfied
                        state.moves.append(Swap(cur_sq=square, new_sq=(new_row, new_col)))
                else:
                    # Adjacent square is empty indicating that it is a legal move
                    state.moves.append(Move(cur_sq=square, new_sq=(new_row, new_col)))

        # Positive and negative rotation is always a legal move for every piece
        state.moves.append(Rotate(cur_sq=square, val=Rotation.NEG))
        state.moves.append(Rotate(cur_sq=square, val=Rotation.POS))


    # Determine result of laser on game board #
    def fire_laser(self, board, laser):
        i, j = laser
        direction = board[i][j].direction

        while True:
            if direction is Direction.NORTH or direction is Direction.SOUTH:
                i += (direction.value - 1)
            else:
                j += (2 - direction.value)

            if not self.in_bounds(i, j):
                print('Laser out of bounds')
                return

            piece = board[i][j]
            if piece is not None:
                face_hit = piece.resolve_hit(direction)
                if face_hit is Face.DESTROY:
                    print('Destroyed {} at ({}, {})'.format(piece, i, j))
                    board[i][j] = None
                    return

                elif face_hit is Face.REFLECT_POS: 
                    direction = Direction((direction.value + 1) % 4)
                    print('Laser reflected {} off {} at ({}, {})'
                        .format(direction.name, piece, i, j))

                elif face_hit is Face.REFLECT_NEG:
                    direction = Direction((direction.value - 1) % 4)
                    print('Laser reflected {} off {} at ({}, {})'
                        .format(direction.name, piece, i, j))

                else:
                    print('Hit {} at ({}, {})'.format(piece, i, j))
                    return
