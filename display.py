import curses
from enum import IntEnum
from utils import SQUARES, ROWS, COLS, Rotate, Color, Kind, Rotation

#TODO: Curses display fails if terminal window is not large enough to draw entire game board
# Avoid crash by cropping game board if window is too small

###############################################################################
# Khet TUI interactive mode controls:                                         #
# - Arrow keys for movement                                                   #
# - Enter to view possible moves/swaps for currently selected piece           #
#   - Choose move by navigating to desired square and pressing Enter          #
# - r / R to initiate positive/negative rotation for currently selected piece #
#   - Finalize rotation with Enter, press any arrow key to cancel             #
###############################################################################


# Unicode symbols representing game pieces
# use case: icons[<kind>][<direction>]
#                   N         E          S         W
icons = {
  Kind.ANUBIS:  ('\u25d3', '\u25d1', '\u25d2', '\u25d0'),
  Kind.PHARAOH: ('\u2625',) * 4,                         # Same icon used as rotation is meaningless
  Kind.PYRAMID: ('\u25e3', '\u25e4', '\u25e5', '\u25e2'),
  Kind.SCARAB:  ('\u2572', '\u2571', '\u2572', '\u2571'),
  Kind.SPHINX:  ('\u2963', '\u2964', '\u2965', '\u2962')
}

# Labels for curses foreground/background color pairs used on game board squares
class SquareColor(IntEnum):
  ACTIVE = 3,
  POSSIBLE_MOVE = 4,
  POSSIBLE_ROTATION = 5

# Size of drawn game board squares
ROW_WIDTH = 5
COL_WIDTH = 7
ROW_LENGTH = COL_WIDTH * COLS
COL_LENGTH = ROW_WIDTH * ROWS


# Determine if current screen position is within drawn game board
def in_bounds(y, x):
  return 0 <= y <= COL_LENGTH and 0 <= x <= ROW_LENGTH


# Return 2D array of curses subwindows where each element represents one game board square
def draw_squares(screen):
  subwins = []
  for i, row in enumerate(SQUARES):
    subwins.append([])
    for j, color in enumerate(row):
      subwins[i].append(screen.subwin(ROW_WIDTH, COL_WIDTH, i * ROW_WIDTH, j * COL_WIDTH))
      subwins[i][j].attrset(curses.color_pair(color))
      subwins[i][j].border()
  return subwins


# Conversion between screen position and 2D index
def idx_from_position(y, x):
  return ((y - 2) // ROW_WIDTH, (x - 3) // COL_WIDTH)


# Conversion between 2D index and screen position
def position_from_idx(i, j):
  return (ROW_WIDTH * i + 2, COL_WIDTH * j + 3)


# Insert piece icon at screen position corresponding to its 2D index
def place_piece(i, j, icon, color, screen):
  screen.addch(*position_from_idx(i, j), icon, curses.color_pair(color) | curses.A_BOLD)


# Modify and redraw game board square with new attributes
def ch_subwin(i, j, attr, subwins):
  subwins[i][j].attrset(attr)
  subwins[i][j].border()
  subwins[i][j].refresh()


# Display current game board using curses
# Interactive move selection available when a game instance is provided
def draw_screen(screen, state, game):
  screen.clear()
  curses.curs_set(0)

  # Piece colors
  curses.init_pair(Color.SILVER, curses.COLOR_CYAN, curses.COLOR_BLACK)
  curses.init_pair(Color.RED, curses.COLOR_RED, curses.COLOR_BLACK)

  # Game board square colors
  curses.init_pair(SquareColor.ACTIVE, curses.COLOR_GREEN, curses.COLOR_BLACK)          
  curses.init_pair(SquareColor.POSSIBLE_MOVE, curses.COLOR_MAGENTA, curses.COLOR_BLACK)   
  curses.init_pair(SquareColor.POSSIBLE_ROTATION, curses.COLOR_YELLOW, curses.COLOR_BLACK) 

  board = state.board[0]
  subwins = draw_squares(screen)
  for i, row in enumerate(board):
    for j, piece in enumerate(row):
      if piece is not None:
        place_piece(i, j, icons[piece.kind][piece.direction], piece.color, screen)
  screen.refresh()

  if game is None:
    # Display current state without selecting an action
    screen.getch()

  else:
    # Provide TUI for interactively selecting an action
    moves = []
    rotation_status = []

    # Initialize active square to the Sphinx of the current player
    screen.move(*position_from_idx(*game.lasers[state.to_move]))

    # Iterate while no move chosen
    while True:
      y, x = screen.getyx()
      new_y, new_x = y, x            # Used to check if player has moved squares after key press
      i, j = idx_from_position(y, x)

      # Color possible move squares
      for action in moves:
        row, col = action.new_sq
        ch_subwin(row, col, curses.color_pair(SquareColor.POSSIBLE_MOVE), subwins)

      # Color currently selected square
      active_color = SquareColor.POSSIBLE_ROTATION if rotation_status else SquareColor.ACTIVE              
      ch_subwin(i, j, curses.color_pair(active_color), subwins)
      screen.refresh()

      key = screen.getch()

      # Movement
      if key == curses.KEY_UP and in_bounds(new_y := y - ROW_WIDTH, x):
        screen.move(new_y, x)
      elif key == curses.KEY_RIGHT and in_bounds(y, new_x := x + COL_WIDTH):
        screen.move(y, new_x)
      elif key == curses.KEY_DOWN and in_bounds(new_y := y + ROW_WIDTH, x):
        screen.move(new_y, x)
      elif key == curses.KEY_LEFT and in_bounds (y, new_x := x - COL_WIDTH):
        screen.move(y, new_x)
      
      # Move/Swap initiation and confirmation of all actions
      elif key == curses.KEY_ENTER or key == ord('\n') or key == ord('\r'):
        if rotation_status:
          # Confirm initiated rotation
          board[i][j].direction = rotation_status[0]
          return Rotate(cur_sq=(i,j), val=rotation_status[1])

        for action in moves:
          if action.new_sq == (i, j):
            # Player has selected a piece to move and the square to move to
            return action

        # Player has selected a piece to move
        moves = []
        game.get_legal_moves(i, j, board, moves, state.to_move)
        moves = [action for action in moves if not isinstance(action, Rotate)]

      # Rotation initiation, confirm piece exists and belongs to the player
      elif (key == ord('r') or key == ord('R')) and (piece := board[i][j]) is not None and piece.color == state.to_move:
          if rotation_status:
            # Current piece already has an active rotation, 
            # restore to original direction before altering again
            piece.direction = rotation_status[0]
            rotation_status = []

          # Save current direction of piece
          rotation_status.append(piece.direction)

          # Save active rotation of piece
          if piece.kind is Kind.SPHINX:
            rotation_status.append(Rotation.FLIP)
          elif key == ord('r'):
            rotation_status.append(Rotation.POS)
          elif key == ord('R'):
            rotation_status.append(Rotation.NEG)

          # Update icon to reflect possible rotation
          piece.rotate(rotation_status[1])
          place_piece(i, j, icons[piece.kind][piece.direction], piece.color, screen)
        
      # Key press resulted in changing to a new square
      if (y, x) != (new_y, new_x):
        if rotation_status:
          # Current piece has an active rotation, restore to original before changing squares
          piece = board[i][j]
          piece.direction = rotation_status[0]
          rotation_status = []  
          place_piece(i, j, icons[piece.kind][piece.direction], piece.color, screen)

        # New square is not in the active square's possible moves
        if not any(idx_from_position(new_y, new_x) in (action.cur_sq, action.new_sq) for action in moves):
          # Clear currently active square
          ch_subwin(i, j, curses.color_pair(SQUARES[i][j]), subwins)

          first = True
          for action in moves:
            # Clear color of move start square
            if first:
              row, col = moves[0].cur_sq
              ch_subwin(row, col, curses.color_pair(SQUARES[row][col]), subwins)
              first = False
            # Clear color of all possible move end squares
            row, col = action.new_sq
            ch_subwin(row, col, curses.color_pair(SQUARES[row][col]), subwins)
          moves = []


# External wrapper providing curses initilization and cleanup for draw_screen
def tui_display(state, game):
  return curses.wrapper(draw_screen, state, game)
