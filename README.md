# Khet

## Notes

### PKN (Peterson Khet Notation)

Similar to the Forsyth-Edwards Notation (FEN) in chess, I have devised my own
notation to describe a Khet position. It is a one-line ASCII string that
encapsulates all the necessary information needed to play a game from a
particular position, minus history for threefold repetition.

A PKN record contains 4 fields, delimited by a space.
1. Piece placement from A1 to J8, where uppercase letters denote silver 
   pieces and lowercase denote red pieces. A series of blank spaces is given by 
   a digit, where 0 represents 10 spaces. A forward slash `/` signifies
   the end of a row. Pieces are represented as such, Anubis='A', pharaoh='R',
   pyramid='P', scarab='S' and sphinx='X'.
2. Piece rotation, in order of placed pieces. Directions are represented by only
   lowercase letters, one for each cardinal direction, 'n', 'e', 's' and 'w'.
2. The color of the active player.
3. The current turn, incremented after the Red player makes a move.

For example, here is the PKN for the starting configuration of the Classic game
arrangement.

```
2PARA3X/7P2/6p3/p1P1SS1p1P/p1P1ss1s1P/3P6/2p7/x3arap2 wnnnnneewwsnsnsneewwssssse s 0
```
