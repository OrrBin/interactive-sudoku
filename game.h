/*
 * game.h
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */

#ifndef GAME_H_
#define GAME_H_
#endif /* GAME_H_ */

typedef struct Cells
{
	int value;
	int isFixed;
}Cell;

typedef struct Boards
{
	Cell cells [][];
	int numOfEmptyCells;
	int rows;
	int cols;
}Board;

void setValueOfCell(Board board, int row, int col, int value);

void clearCell(Board board, int row, int col);

Board initBoard(int rows, int cols, int numOfFixedCells);

