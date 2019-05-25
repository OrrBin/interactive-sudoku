/*
 * util.h
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#ifndef UTIL_H_
#define UTIL_H_



#endif /* UTIL_H_ */

#include "types.h"

void printBoard(Board* board);

int *createRange(int numOfValidValues, int *validIndexes);

int *removeAtIndex(int *array, int size, int idx);

int cellNum(Board* board, int row, int col);

int cellRow(Board* board, int cellNum);

int cellCol(Board* board, int cellNum);

Board* cpyBoard(Board* board, Board* destination);

Cell *cpyCellArray(Cell *src, int size);

Board *cpyBoardAsFixed(Board* board, Board* destination);

int isCellFixed(Board* board, int row, int col);

int isLastCell(Board* board, int row, int col);

int isLastCellInRow(Board* board, int row, int col);

void freeBoard(Board *board);

int isStringsEqual(char *string1, char *string2);

void getStringFromUser();
