from color import Color


class Square(object):

    def __init__(self, color=None, sphinx=False):
        self.__color = color
        self.__sphinx = sphinx

    def getColor(self):
        return self.__color

    def isSphinx(self):
        return self.__sphinx

    def __str__(self):
        if (self.__color):
            return 'SQUARE:' + self.__color.name
        else:
            return 'SQUARE:BLANK'


class Board(object):

    def __init__(self):
        self.__cols = 10
        self.__rows = 8
        self.__squares = [[Square() for j in range(self.__cols)] for i in range(self.__rows)]
        # init RED squares
        for i in range(self.__rows):
            if (i == 0):
                self.__squares[i][0] = Square(Color.RED, True)
            else:
                self.__squares[i][0] = Square(Color.RED)
        # init SILVER squares
        for i in range(self.__rows):
            col = self.__cols - 1
            if (i == col):
                self.__squares[i][col] = Square(Color.SILVER, True)
            else:
                self.__squares[i][col] = Square(Color.SILVER)

    def __str__(self):
        s = ""
        for i in range(self.__rows):
            for j in range(self.__cols):
                s += str(self.__squares[i][j]) + ' '
            s += '\n'
        return s

