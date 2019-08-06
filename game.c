/*
 * game.c
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "solver.h"
#include "parser.h"


int validateRow(Board *board, int row, int col, int value) {
	int i, testCell;
	int currentCell = cellNum(board, row, col);
	for (i = 0; i < board->dimension; i++) {
		testCell = cellNum(board, row, i);
		if (testCell != currentCell && board->cells[testCell].value == value) {
			return 0;
		}
	}
	return 1;
}

int validateCol(Board *board, int row, int col, int value) {
	int i, testCell;
	int currentCell = cellNum(board, row, col);
	for (i = 0; i < board->dimension; i++) {
		testCell = cellNum(board, i, col);
		if (testCell != currentCell && board->cells[testCell].value == value) {
			return 0;
		}
	}
	return 1;
}

int validateBlock(Board *board, int row, int col, int value) {
	int i, j, testCell;
	int blocRow = row / (board->blockHeight);
	int blocCol = col / (board->blockWidth);
	int currentCell = cellNum(board, row, col);

	for (i = blocRow * (board->blockHeight);
			i < blocRow * (board->blockHeight) + board->blockHeight; i++) {
		for (j = blocCol * (board->blockWidth);
				j < blocCol * (board->blockWidth) + board->blockWidth; j++) {
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

	return valid;
}

int setValueOfCell(Board *board, int row, int col, int value) {

	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
	}

	else if (validateValue(board, row, col, value)) {
		board->cells[cellNum(board, row, col)].value = value;
		board->numOfEmptyCells--;
		return 1;
	}

	else {
		printf("Error: value is invalid\n");
	}

	return 0;
}

int clearCell(Board *board, int row, int col) {
	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
		return 0;
	}

	board->cells[cellNum(board, row, col)].value = 0;
	board->numOfEmptyCells++;

	return 1;
}

void hint(Board *board, int row, int col) {
	printf("Hint: set cell to %d\n",
			board->solution[cellNum(board, row, col)].value);
}

void validate(Board *board) {
	int isSuccess;
	Board *resultBoard = (Board *) malloc(sizeof(Board));
	Board *fixedBoard = cpyBoardAsFixed(board, resultBoard);
	isSuccess = recursiveBackTracking(fixedBoard, resultBoard);
	if (isSuccess) {
		board->solution = resultBoard->cells;
		printf("Validation passed: board is solvable\n");
	} else {

		printf("Validation failed: board is unsolvable\n");
	}
}

void playTurn(Board **boardP) {
	char *result;
	char cmd[MAX_CHARS_IN_COMMAND];
	result = getStringFromUser(cmd);
	if (!result) {
		printf("Exiting...\n");
		freeBoard(*boardP);
		exit(1);
	}
	parseCommand(boardP, cmd);
}

void exitGame(Board *board) {
	freeBoard(board);
	printf("Exiting...\n");
	exit(0);
}

Board* initGameWithNumberOfCellsToFill(int dimension, int blockHeight,
		int blockWidth, int numberOfCellsToFill) {
	int i = 0, randCol, randRow;
	Cell *cells1, *cells2;
	Board *solution = (Board *) malloc(sizeof(Board));
	Board *board = (Board *) malloc(sizeof(Board));

	cells1 = (Cell *) malloc((dimension * dimension) * sizeof(Cell));
	cells2 = (Cell *) malloc((dimension * dimension) * sizeof(Cell));

	for (i = 0; i < dimension * dimension; i++) {
		cells1[i].value = 0;
		cells1[i].isFixed = 0;
		cells2[i].value = 0;
		cells2[i].isFixed = 0;
	}

	i = 0;

	board->dimension = dimension;
	board->cells = cells1;
	board->numOfEmptyCells = dimension * dimension;
	board->blockHeight = blockHeight;
	board->blockWidth = blockWidth;

	solution = cpyBoard(board, solution);

	randomizeBackTracking(solution, solution);

	board->solution = cpyCellArray(solution->cells, dimension * dimension);

	while (i < numberOfCellsToFill) {
		randCol = rand() % dimension;
		randRow = rand() % dimension;
		if (!board->cells[cellNum(board, randRow, randCol)].isFixed) {
			board->cells[cellNum(board, randRow, randCol)] =
					solution->cells[cellNum(board, randRow, randCol)];
			board->cells[cellNum(board, randRow, randCol)].isFixed = 1;
			board->numOfEmptyCells--;
			i++;
		}
	}

	free(solution->cells);
	free(solution);

	printBoard(board);

	return board;
}

Board* initGame(int dimension, int blockHeight, int blockWidth) {
	int input = -10;
	int numberOfCellsToFill = -1;
	printf("Please enter the number of cells to fill [0-80]:\n");

	input = scanf("%d", &numberOfCellsToFill);

	numberOfCellsToFill = 6;

	if (input == EOF) {
		printf("Exiting...\n");
		exit(0);
	}

	while ((numberOfCellsToFill < 0 || numberOfCellsToFill > dimension*dimension - 1) && input != EOF) {
		printf(
				"Error: invalid number of cells to fill (should be between 0 and 80)\n");
		printf("Please enter the number of cells to fill [0-80]:\n");
		input = scanf("%d", &numberOfCellsToFill);
	}

	if (input == EOF) {
		printf("Exiting...\n");
		exit(0);
	}

	return initGameWithNumberOfCellsToFill(dimension, blockHeight, blockWidth,
			numberOfCellsToFill);

}

Board* restart(Board *board) {
	int dimension = board->dimension, blockHeight = board->blockHeight, blockWidth =
			board->blockWidth;
	freeBoard(board);
	return initGame(dimension, blockHeight, blockWidth);
}

int isGameOver(Board *board) {
	return board->numOfEmptyCells == 0;
}
