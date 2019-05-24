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

void clearCell(Board *board, int row, int col) {
	setValueOfCell(board, row, col, 0);
}


int validateRow(Board *board, int row, int col, int value) {
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

int validateCol(Board *board, int row, int col, int value) {
	printf("validate col\n");
	int i, testCell;
	int currentCell = cellNum(board, row, col);
	for (i = 0; i < board->rows; i++) {
		testCell = cellNum(board, i, col);
		printf("col cell num : %d\n", testCell);
		if (testCell != currentCell && board->cells[testCell].value == value) {
			printf("Not valid\n");
			return 0;
		}
	}
	printf("Valid\n");
	return 1;
}

int validateBlock(Board *board, int row, int col, int value) {
	int i, j, testCell;
	int blocRow = row / (board->blockHeight);
	int blocCol = col / (board->blockWidth);
//	printf("%d, %d, %d , %d\n", row, col, blocRow, blocCol);
	int currentCell = cellNum(board, row, col);

	for (i = blocRow * (board->blockHeight); i < blocRow * (board->blockHeight) + board->blockHeight; i++) {
		for (j = blocCol * (board->blockWidth); j < blocCol * (board->blockWidth) + board->blockWidth; j++) {
			testCell = cellNum(board, i, j);
			if (testCell != currentCell
					&& board->cells[testCell].value == value) {
				return 0;
			}
		}
	}
	return 1;
}

int validateValue(Board *board, int row, int col, int value) {
	int valid;
	valid = validateBlock(board, row, col, value)
			&& validateRow(board, row, col, value)
			&& validateCol(board, row, col, value);

	printf("validate value: %d, %d\n", valid, value);

	return valid;
}

