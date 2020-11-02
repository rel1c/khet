from const import Color

class Board(object):

    def __init__(self):
        self.squares = (
            (Color.RED, Color.SILVER, None, None, None, None, None, None, Color.RED, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, None, None, None, None, None, None, None, None, Color.SILVER), 
            (Color.RED, Color.SILVER, None, None, None, None, None, None, Color.RED, Color.SILVER))

    def __str__(self):
        s = ""
        for x in range(len(self.squares)):
            for y in range(len(self.squares[x])):
                if self.squares[x][y] is Color.RED:
                    ch = ' R '
                elif self.squares[x][y] is Color.SILVER:
                    ch = ' S '
                else:
                    ch = ' + '
                s += ch + ' '
            s += '\n'
        return s
