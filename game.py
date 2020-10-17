"""
Move((x1, y1), (x2, y2))
    - move a piece from (x1, y1) to (x2, y2)
    - check if move is legal
    - check move consequences (scarab)
    - execute move

pieces[[P1, P2, ..., Pi], ..., [ ..., Pn]]
    - each players active pieces on the board
    - pieces are "idependent" of board as they move on it
    - each piece has location as index on 2D array
"""
Class Game(object):

    COLS = 10
    ROWS = 8
    pieces = [[None for col in range(COLS)] for row in range(ROWS)]

    def __init__():
        pass

    def movePiece():
        pass

    def isOver():
        pass

    def fireLaser():
        pass
