import copy
import utils
from collections import Counter
from game import Game, GameState
from utils import Move, Rotate, Swap, Color, Direction, Face, Kind, Rotation
from display import tui_display


# Object class which embodies a game piece.
class Piece(object):

    # Look-up table to generate the faces of a piece
    FACES = {
        Kind.ANUBIS: (Face.ABSORB, Face.DESTROY, Face.DESTROY, Face.DESTROY),
        Kind.PHARAOH: (Face.DESTROY, Face.DESTROY, Face.DESTROY, Face.DESTROY),
        Kind.PYRAMID: (Face.REFLECT_NEG, Face.REFLECT_POS, Face.DESTROY, Face.DESTROY),
        Kind.SCARAB: (Face.REFLECT_NEG, Face.REFLECT_POS, Face.REFLECT_NEG, Face.REFLECT_POS),
        Kind.SPHINX: (Face.ABSORB, Face.ABSORB, Face.ABSORB, Face.ABSORB)
    }

    # Each piece corresponds to the three digit number in a game layout.
    def __init__(self, color, kind, direction):
        self.color = color
        self.kind = kind
        self.direction = direction
        self.faces = Piece.FACES[kind]

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            # Ensure other is a Piece object
            return self.color == other.color and self.kind == other.kind and self.direction == other.direction
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    #TODO: Making a mutable object hashable causes problems if the object is used as the key to a dictionary
    # as the hash is only calculated at creation. In this case the problem is avoided because Piece objects 
    # are never used directly as a key and the dictionary of game board hashes is treated as immutable.
    # However, would probably be a "best practice" to have rotate() method create new Piece objects instead of
    # mutating direction state
    def __hash__(self):
        # Piece objects with the same color, kind, and direction will evaluate as equal and hash to same value
        return hash((self.color, self.kind, self.direction))
        
    # Resolves a laser hit on a piece via the face look-up table and the laser's direction.
    def resolve_hit(self, laser_direction):
        hit = (2 + laser_direction.value - self.direction.value) % 4
        return self.faces[hit]

    # Rotates a piece clockwise or counter-clockwise, or flips it #
    def rotate(self, rotation):
        assert -1 <= rotation <= 1
        if not rotation: # Then flip
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
        return 0 <= row < utils.ROWS and 0 <= col < utils.COLS 

    # Return the color of the opposing player #
    @staticmethod
    def opponent_color(player_color):
        return player_color % 2 + 1  # Color enum begins at 1 instead of 0

    # Calculate the hash of a game board to track the number of times it has been seen in a game #
    @staticmethod
    def hash_game(board):
        return hash(tuple(map(tuple, board)))

    # Construct 2D Piece object array from provided layout #
    def __init__(self, layout=utils.Layout.CLASSIC):
        self.lasers = {Color.SILVER: (), Color.RED: ()}  # The sphinx locations for each player

        initial_board = [[None] * utils.COLS for _ in range(utils.ROWS)]
        for i, row in enumerate(layout):
            for j, square in enumerate(row):
                if square:
                    # square is a three digit number indicating the color, kind, and direction of a piece
                    color = Color(square // 100)
                    kind = Kind((square // 10) % 10)
                    direction = Direction(square % 10)
                    initial_board[i][j] = Piece(color, kind, direction)
                    if kind is Kind.SPHINX:
                        self.lasers[color] = (i, j)

        # Contains the current game board, its hash,
        # and a mapping between game board hashes and the number of times they have been seen in a game
        board_state = (
            initial_board,                                  
            initial_hash := self.hash_game(initial_board), 
            Counter({initial_hash: 1})
        ) 
        self.initial = GameState(to_move=Color.SILVER, utility=0, board=board_state, moves=[])


    # Return all of a player's legal moves #
    def actions(self, state):
        board = state.board[0]
        for i, row in enumerate(board):
            for j, _ in enumerate(row):
                self.get_legal_moves(i, j, board, state.moves, state.to_move)
        return state.moves


    # Modify the game board according to the selected move #
    # log_result determines if the result of each laser fire is logged to stdout
    def result(self, state, action, log_result=False):
        board, _, times_seen = state.board
        board = copy.deepcopy(board)           # Boards must be immutable for algorithms that reuse previous states
        times_seen = copy.deepcopy(times_seen) # Tracking of seen game boards must also be immutable to enforce distinct states

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

        utility = self.fire_laser(board, self.lasers[state.to_move], log_result)
        board_hash = self.hash_game(board)
        times_seen[board_hash] += 1

        return GameState(to_move=self.opponent_color(state.to_move),
                         utility=utility,
                         board=(board, board_hash, times_seen), 
                         moves=[])


    # Retrieve utility of a game state #
    def utility(self, state, player):
        return state.utility if player is Color.SILVER else -state.utility


    # Determine if game has come to an end #
    def terminal_test(self, state):
        _, board_hash, times_seen = state.board
        return state.utility != 0 or times_seen[board_hash] == utils.DRAW_CONDITION


    # Display game state in human readable format #
    def display(self, state, as_tui=True, interactive=False):
        if as_tui:
            return tui_display(state, self if interactive else None)
        else:
            # Pieces displayed as three digit numbers with each digit representing color, kind, and direction, respectively
            board = state.board[0]
            for row in board:
                for square in row:
                    if square:
                        print(square.values(), end=' ')
                    else:
                        print("---", end=' ')
                print()
         

    # Find all legal moves for a piece #
    def get_legal_moves(self, i, j, board, moves, player_color):
        square = i, j
        piece = board[i][j]

        if piece is None or piece.color != player_color:
            # There is no piece at the current square or the piece belongs to the opponent
            # and therefore cannot have any legal moves for the player
            return
        if piece.kind is Kind.SPHINX:
            # Only possible move for Sphinx is to flip rotation
            moves.append(Rotate(cur_sq=square, val=Rotation.FLIP))
            return

        # Iterate over the relative indices of the 8 surrounding squares to check movement/swap possibilities
        for row_offset, col_offset in Khet.ordinals:    
            new_i = i + row_offset
            new_j = j + col_offset
            if self.in_bounds(new_i, new_j) and utils.SQUARES[new_i][new_j] != self.opponent_color(player_color):
                # Square is both on the board and not the opponent's color
                if (adj_piece := board[new_i][new_j]) is not None:
                    # Adjacent square has a piece
                    if piece.kind is Kind.SCARAB and (adj_piece.kind is Kind.PYRAMID or adj_piece.kind is Kind.ANUBIS):
                        # Requirements for Scarab swap are satisfied
                        moves.append(Swap(cur_sq=square, new_sq=(new_i, new_j)))
                else:
                    # Adjacent square is empty indicating that it is a legal move
                    moves.append(Move(cur_sq=square, new_sq=(new_i, new_j)))

        # Negative and positive rotation is always a legal move for every piece
        moves.append(Rotate(cur_sq=square, val=Rotation.NEG))
        moves.append(Rotate(cur_sq=square, val=Rotation.POS))


    # Determine result of firing laser on game board #
    def fire_laser(self, board, laser, log_result):
        utility = 0
        i, j = laser
        direction = board[i][j].direction

        while True:
            if direction is Direction.NORTH or direction is Direction.SOUTH:
                i += (direction.value - 1)
            else:
                j += (2 - direction.value)

            if not self.in_bounds(i, j):
                if log_result: 
                    print('Laser out of bounds')
                return utility

            if (piece := board[i][j]) is not None:
                face_hit = piece.resolve_hit(direction)
                if face_hit is Face.DESTROY:
                    if log_result:
                        print('Destroyed {} at ({}, {})'.format(piece, i, j))
                    if piece.kind is Kind.PHARAOH:
                        # Game is over on elimination of either player's Pharaoh
                        utility = 1 if piece.color is Color.RED else -1
                    board[i][j] = None
                    return utility

                elif face_hit is Face.REFLECT_POS: 
                    direction = Direction((direction.value + 1) % 4)
                    if log_result:
                        print('Laser reflected {} off {} at ({}, {})'
                            .format(direction.name, piece, i, j))

                elif face_hit is Face.REFLECT_NEG:
                    direction = Direction((direction.value - 1) % 4)
                    if log_result:
                        print('Laser reflected {} off {} at ({}, {})'
                            .format(direction.name, piece, i, j))

                else:
                    if log_result:
                        print('Hit {} at ({}, {})'.format(piece, i, j))
                    return utility
