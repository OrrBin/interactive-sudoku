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

int cellNum(Board* board, int row, int col);

Board* cpyBoard(Board* board, Board* destination);

int isCellFixed(Board* board, int row, int col);

int isLastCell(Board* board, int row, int col);

int isLastCellInRow(Board* board, int row, int col);

void freeBoard(Board *board);

int isStringsEqual(char *string1, char *string2);
