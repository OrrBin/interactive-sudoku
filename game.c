/*
 * game.c
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void setValueOfCell(Board *board, int row, int col, int value) {
	board->cells[cellNum(board, row, col)].value = value;
}

int checkValidRow(Board *board, int row, int col, int value) {
	int i, testCell;
	int currentCell = cellNum(board, row, col);
	for (i = 0; i < board->cols; i++) {
		testCell = cellNum(board, row, i);
		if (testCell != currentCell && board->cells[testCell].value == value) {
			return 0;
		}
	}
	return 1;
}

int checkValidCol(Board *board, int row, int col, int value) {
	int i, testCell;
	int currentCell = cellNum(board, row, col);
	for (i = 0; i < board->rows; i++) {
		testCell = cellNum(board, i, col);
		if (testCell != currentCell && board->cells[testCell].value == value) {
			return 0;
		}
	}
	return 1;
}

int checkValidBlock(Board *board, int row, int col, int value) {
	int i, j, testCell;
	int blocRow = row / (board->blockHeight);
	int blocCol = col/ (board->blockWidth);
	printf("%d, %d, %d , %d\n",row, col, blocRow, blocCol);
	int currentCell = cellNum(board, row, col);

	for (i = blocRow * board->blockHeight; i < board->blockHeight; i++) {
		for (j = blocCol * board->blockWidth; j < board->blockWidth; j++) {
			testCell = cellNum(board, i, j);
			if (testCell != currentCell && board->cells[testCell].value == value) {
				return 0;
			}
		}
	}
	return 1;
}

int checkValidValue(Board *board, int row, int col, int value) {
	return
			checkValidBlock(board, row, col, value);
//		 checkValidRow(board, row, col, value);
//			&& checkValidCol(board, row, col, value);
}

