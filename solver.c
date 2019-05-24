/*
 * solver.c
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */
#include <stdio.h>

#include "util.h"
#include "game.h"

int recursiveBackTrackingStep(Board *board, int row, int col) {
	int idx, result;

	printf("Got row,col: %d, %d\n", row, col);

	if (isCellFixed(board, row, col)) {
		if (isLastCell(board, row, col)) {
			return 1;
		}
		if (isLastCellInRow(board, row, col))
			return recursiveBackTrackingStep(board, row + 1, 0);

		return recursiveBackTrackingStep(board, row, col + 1);
	}

	for (idx = 1; idx <= board->rows; idx++) {
		if (validateValue(board, row, col, idx)) {
			setValueOfCell(board, row, col, idx);
			if (!isLastCell(board, row, col)) {
				if (isLastCellInRow(board, row, col)) {
					result = recursiveBackTrackingStep(board, row + 1, 0);
				} else
					result = recursiveBackTrackingStep(board, row, col + 1);

			}
			if (result)
				return 1;
		}
	}
	clearCell(board, row, col);
	return 0;
}

int recursiveBackTracking(Board *board, Board *result) {
	int isSuccess;
	printf("going to cpy board\n");
	cpyBoard(board, result);
	printf("cpyd board\n");
	isSuccess = recursiveBackTrackingStep(result, 0, 0);


	return isSuccess;
}
