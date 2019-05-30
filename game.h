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

int setValueOfCell(Board *board, int row, int col, int value);

int clearCell(Board *board, int row, int col);

Board initBoard(int rows, int cols, int numOfFixedCells);

Board* initGame(int dimension, int blockHeight, int blockWidth);

void playTurn(Board **boardP);

void hint(Board *board, int row, int col);

void validate(Board *board);

Board* restart(Board *board);

void exitGame(Board *board);

int isGameOver(Board *board);
