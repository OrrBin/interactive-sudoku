/*
 * solver.c
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "game.h"

int handleCell(Board *board, int row, int col, int value,
		int (*callback)(Board *, int, int)) {
	int result;
	setValueOfCell(board, row, col, value);
	if (!isLastCell(board, row, col)) {
		if (isLastCellInRow(board, col)) {
			result = callback(board, row + 1, 0);
		} else
			result = callback(board, row, col + 1);
	}
	return result;

}

int recursiveBackTrackingStep(Board *board, int row, int col) {
	int idx, result;

	if (isCellFixed(board, row, col)) {
		if (!validateValue(board, row, col,
				board->cells[cellNum(board, row, col)].value))
			return 0;
		if (isLastCell(board, row, col)) {
			return 1;
		}
		if (isLastCellInRow(board, col))
			return recursiveBackTrackingStep(board, row + 1, 0);

		return recursiveBackTrackingStep(board, row, col + 1);
	}

	for (idx = 1; idx <= board->rows; idx++) {
		if (validateValue(board, row, col, idx)) {
			result = handleCell(board, row, col, idx,
					recursiveBackTrackingStep);
			if (result)
				return 1;
		}
	}
	clearCell(board, row, col);
	return 0;
}

int recursiveBackTracking(Board *board, Board *destination) {
	int isSuccess;
	destination = cpyBoard(board, destination);
	isSuccess = recursiveBackTrackingStep(destination, 0, 0);

	return isSuccess;
}

int checkValidValuesNum(Board *board, int row, int col) {
	int idx, numOfValidValues = 0;
	for (idx = 1; idx <= board->rows; idx++) {
		if (validateValue(board, row, col, idx)) {
			numOfValidValues++;
		}
	}
	return numOfValidValues;
}

int *checkValidValues(Board *board, int row, int col, int *validValues) {
	int idx, counter, numOfValidValues = 0;
	int *flags = calloc(board->cols, sizeof(int));
	for (idx = 1; idx <= board->rows; idx++) {
		if (validateValue(board, row, col, idx)) {
			flags[idx - 1] = 1;
			numOfValidValues++;
		}
	}

	validValues = (int *) malloc(numOfValidValues * sizeof(int));

	counter = 0;
	for (idx = 0; idx < board->cols; idx++) {
		if (flags[idx] == 1)
			validValues[counter++] = idx + 1;
	}

	free(flags);

	return validValues;

}

int randomizeBackTrackingStep(Board *board, int row, int col) {
	int idx, result, currentValueIdx, currentIdx, currentValue = 0;
	int *validValues = NULL, numOfValidValues = 0, *validIndexes = NULL;

	numOfValidValues = checkValidValuesNum(board, row, col);
	validValues = checkValidValues(board, row, col, validValues);


	if (numOfValidValues == 1) {
		currentValue = validValues[0];
		result = handleCell(board, row, col, currentValue,
				randomizeBackTrackingStep);
		if (result)
			return 1;

	} else if (numOfValidValues > 1) {
		validIndexes = createRange(numOfValidValues, validIndexes);

		for (idx = 0; idx < numOfValidValues; idx++) {
			if ((numOfValidValues - idx) == 1) {
				currentValue = validValues[validIndexes[0]];
				result = handleCell(board, row, col, currentValue,
						randomizeBackTrackingStep);
				if (result)
					return 1;

				break;
			}

			currentIdx = rand() % (numOfValidValues - idx);
			currentValueIdx = validIndexes[currentIdx];
			currentValue = validValues[currentValueIdx];
			validIndexes = removeAtIndex(validIndexes, (numOfValidValues - idx),
					currentIdx);
			result = handleCell(board, row, col, currentValue,
					randomizeBackTrackingStep);
			if (result)
				return 1;

		}
	}

	clearCell(board, row, col);
	return 0;
}

int randomizeBackTracking(Board* board, Board* destination) {
	int isSuccess;
	destination = cpyBoard(board, destination);
	isSuccess = randomizeBackTrackingStep(destination, 0, 0);

	return isSuccess;
}

