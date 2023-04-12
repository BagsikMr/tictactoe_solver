# tictactoe_solver

## Table of contents
* [General info](#general-info)
* [Setup](#setup)
* [TODO](#todo)

## General info
The program implements the minimax algorithm used in a Tic-Tac-Toe game solver, along with optimizations such as alpha-beta pruning and k-beam search.

GEN_ALL_POS_MOV - generate all possible moves.

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER - generate all possible moves and cut if game is over.

SOLVE_GAME_STATE - the program will output which player will win after optimal moves.

## Setup
Just run sln.

The program has the following commands which were described above:	<br />
	<br />
- "GEN_ALL_POS_MOV"	<br />
- "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER"	<br />
- "SOLVE_GAME_STATE"	<br />
The next four inputs are:	<br />
	<br />
- board width (N)	<br />
- board height (M)	<br />
- victory condition	<br />
- current player	<br />
<br />


The next input is the board state:	<br />
- N*M input of '0', '1', or '2'	<br />
Example input:	<br />
GEN_ALL_POS_MOV	<br />
3 3 3 1	<br />
0 0 0	<br />
0 0 0	<br />
0 0 0	<br />
	<br />

## TODO
-Write better readme.

-Create a visualization of this, preferably a tic-tac-toe game with a bot.
