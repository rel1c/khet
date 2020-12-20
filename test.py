import sys
from game import *
from khet import *

# Argument to play_game method
def tui_player(game, state):
  print('\nPress Enter to select move') # For now -- that way able to check log of laser fire for MCTS
  sys.stdin.read(1)
  move = game.display(state, interactive=True)
  i, j = move.cur_sq
  print(f'You chose: {state.board[0][i][j]} : {move}') # Confirm TUI accuracy (for now)
  return move

# Print actions in a human-readable way
def display_actions(moves):
  for move in moves:
    print(move)

# Check game board hashing
def test_times_seen(game):
  game.display(game.initial)
  state = game.result(game.initial, Rotate(cur_sq=(6,7), val=Rotation.POS))
  game.display(state)
  state = game.result(state, Rotate(cur_sq=(1,2), val=Rotation.POS))
  game.display(state)
  state = game.result(state, Rotate(cur_sq=(6,7), val=Rotation.NEG))
  game.display(state)
  state = game.result(state, Rotate(cur_sq=(1,2), val=Rotation.NEG))
  game.display(state)

  # Check final board and initial board are identical
  assert game.initial.board[0] == state.board[0]
  # Confirm final counter has seen hash of initial game board twice
  assert state.board[2][game.hash_game(game.initial.board[0])] == 2



k = Khet()
# test_times_seen(k)
# print(monte_carlo_tree_search(k.initial, k))

# print(f'MCTS final utility: {k.play_game(mcts_player, tui_player)}')
print(f'MCTS final utility: {k.play_game(mcts_player, random_player)}')

# k = Khet()
# new_state = k.result(k.initial, k.actions(k.initial)[0])
# print(new_state.to_move)
# k.display(new_state)
# display_actions(k.actions(new_state))
