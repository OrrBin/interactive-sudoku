/*
 * game.h
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */

#ifndef GAME_H_
#define GAME_H_
#endif /* GAME_H_ */


int validateValue(Board *board, int row, int col, int value);

void setValueOfCell(Board *board, int row, int col, int value);

void clearCell(Board *board, int row, int col);

Board initBoard(int rows, int cols, int numOfFixedCells);

void hint(Board *board, int row, int col);

void validate(Board *board);

void restart(Board *board);

void exitGame(Board *board);

