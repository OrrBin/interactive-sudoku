/*
 * game.h
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */

#ifndef GAME_H_
#define GAME_H_

#include "util.h"
#include "gll.h"
/*
 * validateValue gets a board, row, col, and value.
 * it checks whether or not value might be set to
 * the cell board[row][col]. i.e. there are no
 * conflicts with same row/col/block.
 */
int validateValue(Board *board, int row, int col, int value);

/*
 * setValueOfCell gets a board, row, col and value.
 * It check if setting board[row][col] is possible.
 * If yes, it is do it. Else, it prints the relevant
 * error.
 */
int setValueOfCell(Board *board, int row, int col, int value);

/*
 * clearCell clears the cell board[row][col].
 * if cell is fixed, it's print relevant error
 * and skips the command.
 */
int clearCell(Board *board, int row, int col);

/*
 * initGame asks the user for numberOfCellsToFill input
 * and return a pointer to a board with the desired parameters
 */
Board* initGame(int test);

/*
 * initiates game with specified parameters
 */
Board* initGameWithNumberOfCellsToFill(int dimension, int blockHeight,
		int blockWidth, int numberOfCellsToFill);

/*
 * playTurn asks the user for command input,
 * and call for the relevant function to
 * execute it.
 */
void playTurn(Board **boardP, gll_t *moveList, gll_node_t **curr);

/*
 * hint gets from user board, row and col.
 * it expose the value of board->solution[row][col].
 */
void hint(Board *board, int row, int col);

/*
 * checks whether or not there is a valid solution
 * to the current board. If there is a solution it
 * saves it in board->solution and lets the user know.
 * Else, it's print relevant message.
 */
void validate(Board *board);

/*
 * Finds the number of existing solution to the given board
 */
int findNumberOFSolutions(Board *board);

/*
 * Fills cells with only one legal value.
 * If doPrint is not 0, then prints every change
 */
void autoFillBoard(Board *board, enum boolean);

/*
 * restart free the memory used for the current board
 * and initialize new board.
 */
Board* restart(Board *board);

/*
 * free the memory and exit the game.
 */
void exitGame(Board *board);

int findErrors(Board *board);

/*
 * checks whether or not game completed.
 */
int isGameOver(Board *board);

#endif /* GAME_H_ */
