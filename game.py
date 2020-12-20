import random
import numpy as np
from collections import namedtuple
from utils import Move, Rotate, Swap, Rotation, MCT_Node, ucb


## State tuple for abstract Game class
GameState = namedtuple('GameState', 'to_move, utility, board, moves')


# ______________________________________________________________________________
# Game Theory algorithms
def minmax_decision(state, game):
    """Given a state in a game, calculate the best move by searching
    forward all the way to the terminal states. [Figure 5.3]"""
    player = game.to_move(state)
    def max_value(state):
        if game.terminal_test(state):
            return game.utility(state, player)
        v = -np.inf
        for a in game.actions(state):
            v = max(v, min_value(game.result(state, a)))
        return v
    def min_value(state):
        if game.terminal_test(state):
            return game.utility(state, player)
        v = np.inf
        for a in game.actions(state):
            v = min(v, max_value(game.result(state, a)))
        return v
    # Body of minmax_decision:
    return max(game.actions(state), key=lambda a: min_value(game.result(state, a)))


def monte_carlo_tree_search(state, game, N=500):
    def select(n):
        """select a leaf node in the tree"""
        if n.children:
            return select(max(n.children.keys(), key=ucb))
        else:
            return n

    def expand(n):
        """expand the leaf node by adding all its children states"""
        if not n.children and not game.terminal_test(n.state):
            n.children = {MCT_Node(state=game.result(n.state, action), parent=n): action
                        for action in game.actions(n.state)}
        return select(n)

    def simulate(game, state):
        """simulate the utility of current state by random picking a step"""
        player = game.to_move(state)
        while not game.terminal_test(state):
            action = random.choice(list(game.actions(state)))
            state = game.result(state, action)
        v = game.utility(state, player)
        return -v
   
    def backprop(n, utility):
        """passing the utility back to all parent nodes"""
        if utility > 0:
            n.U += utility
        # if utility == 0:
        #     n.U += 0.5
        n.N += 1
        if n.parent:
            backprop(n.parent, -utility)
   
    root = MCT_Node(state=state)

    for _ in range(N):
        leaf = select(root)
        child = expand(leaf)
        result = simulate(game, child.state)
        backprop(child, result)

    max_state = max(root.children, key=lambda p: p.N)
    return root.children.get(max_state)


# ______________________________________________________________________________
# Player functions that can be passed as arguments to play_game method
def query_player(game, state):
    """Make a move by querying standard input."""
    print("\ncurrent state:")
    game.display(state)
    print("\navailable moves:")
    for move in game.actions(state):
        print(move)
    # print("available moves: {}".format(game.actions(state)))
    print("")
    move = None
    if game.actions(state):
        move_string = input('Your move? ')
        try:
            move = eval(move_string, globals())
        except NameError:
            move = move_string
    else:
        print('no legal moves: passing turn to next player')
    return move

def minmax_player(game, state):
    return minmax_decision(state, game)

def mcts_player(game, state):
    print("\nShhhh I'm thinking.........")
    move = monte_carlo_tree_search(state, game)
    i, j = move.cur_sq
    print(f'I choose: {state.board[0][i][j]} : {move} ')
    return move

def random_player(game, state):
    print("\nUhhhh anything will do!")
    move = random.choice(game.actions(state)
    i, j = move.cur_sq
    print(f'I choose: {state.board[0][i][j]} : {move} ')
    return move

# ______________________________________________________________________________
# AIMA abstract class providing a model for all games
class Game:
    """A game is similar to a problem, but it has a utility for each
    state and a terminal test instead of a path cost and a goal
    test. To create a game, subclass this class and implement actions,
    result, utility, and terminal_test. You may override display and
    successors or you can inherit their default methods. You will also
    need to set the .initial attribute to the initial state; this can
    be done in the constructor."""

    def actions(self, state):
        """Return a list of the allowable moves at this point."""
        raise NotImplementedError

    def result(self, state, move):
        """Return the state that results from making a move from a state."""
        raise NotImplementedError

    def utility(self, state, player):
        """Return the value of this final state to player."""
        raise NotImplementedError

    def terminal_test(self, state):
        """Return True if this is a final state for the game."""
        return not self.actions(state)

    def to_move(self, state):
        """Return the player whose move it is in this state."""
        return state.to_move

    def display(self, state):
        """Print or otherwise display the state."""
        print(state)

    def __repr__(self):
        return '<{}>'.format(self.__class__.__name__)


# Modifying this to provide argument to result that indicates it should log game changes
# log_result defaults to False to avoid algorithms from printing every time laser is fired
# Maybe this is possible without modifying base class but this works for now
    def play_game(self, *players):
        """Play an n-person, move-alternating game."""
        state = self.initial
        while True:
            for player in players:
                move = player(self, state)
                state = self.result(state, move, log_result=True)
                if self.terminal_test(state):
                    self.display(state)
                    return self.utility(state, self.to_move(self.initial))
