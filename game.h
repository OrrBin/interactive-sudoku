/*
 * game.h
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */

#ifndef GAME_H_
#define GAME_H_
#endif /* GAME_H_ */


int checkValidValue(Board *board, int row, int col, int value);

void setValueOfCell(Board *board, int row, int col, int value);

void clearCell(Board board, int row, int col);

Board initBoard(int rows, int cols, int numOfFixedCells);

