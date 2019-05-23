/*
 * solver.c
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */
#include <stdio.h>

#include "util.h"
#include "game.h"

Board *recursiveBackTrackingStep(Board *board, int row, int col) {
	int idx;

	printf("Got row,col: %d, %d\n", row, col);

	if (isCellFixed(board, row, col)) {
//		printf("cell fixed");
		if (isLastCellInRow(board, row, col))
			return recursiveBackTrackingStep(board, row + 1, 0);

		return recursiveBackTrackingStep(board, row, col + 1);
	}
//	printf("cell NOT fixed");

	for (idx = 1; idx <= 9; idx++) {
		if (checkValidValue(board, row, col, idx)) {
			setValueOfCell(board, row, col, idx);
			if (!isLastCell(board, row, col)) {
				if (isLastCellInRow(board, row, col)) {
					board = recursiveBackTrackingStep(board, row + 1, 0);
				}

				board = recursiveBackTrackingStep(board, row, col + 1);
			}
			if (board != NULL)
				return board;
		}
	}

	return NULL;
}

Board *recursiveBackTracking(Board *board, Board *result) {
	printf("going to cpy board\n");
	cpyBoard(board, result);
	printf("cpyd board\n");
	return recursiveBackTrackingStep(result, 0, 0);
}
