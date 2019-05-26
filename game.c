/*
 * game.c
 *
 *  Created on: 22 ·Ó‡È 2019
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
	for (i = 0; i < board->cols; i++) {
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
	for (i = 0; i < board->rows; i++) {
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

void setValueOfCell(Board *board, int row, int col, int value) {

	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
	}

	else if (validateValue(board, row, col, value)) {
		board->cells[cellNum(board, row, col)].value = value;
		board->numOfEmptyCells--;
	}

	else {
		printf("Error: value is invalid\n");
	}
}

void clearCell(Board *board, int row, int col) {
	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
	}

	board->cells[cellNum(board, row, col)].value = 0;
	board->numOfEmptyCells++;
}

void hint(Board *board, int row, int col) {
	printf("Hint: set cell to %d\n",
			board->solution[cellNum(board, row, col)].value);
}

void validate(Board *board) {
	int isSuccess;
	Board *resultBoard = (Board *) malloc(sizeof(Board));
	Board *fixedBoard = cpyBoardAsFixed(board, resultBoard);
	//printBoard(fixedBoard);
	isSuccess = recursiveBackTracking(fixedBoard, resultBoard);
	if (isSuccess) {
		board->solution = resultBoard->cells;
		printf("Validation passed: board is solvable\n");
	} else {

		printf("Validation failed: board is unsolvable\n");
	}
}

void playTurn(Board **boardP) {
	char cmd[MAX_CHARS_IN_COMMAND];
	getStringFromUser(cmd);
	parseCommand(boardP, cmd);
}

void exitGame(Board *board) {
	freeBoard(board);
	printf("ExitingÖ\n");
	exit(0);
}

Board* initGameWithNumberOfCellsToFill(int dimension, int blockHeight, int blockWidth, int numberOfCellsToFill)
{
	int i=0, randX, randY;
	Cell *cells1, *cells2;
	Board *solution = (Board *) malloc(sizeof(Board));
	Board *board = (Board *) malloc(sizeof(Board));

	cells1 = (Cell *) malloc((dimension*dimension) * sizeof(Cell));
	cells2 = (Cell *) malloc((dimension*dimension) * sizeof(Cell));

	for (i = 0; i < dimension*dimension; i++)
	{
		cells1[i].value = 0;
		cells1[i].isFixed = 0;
		cells2[i].value = 0;
		cells2[i].isFixed = 0;
	}

	i=0;

	board->rows=dimension;
	board->cols=dimension;
	board->cells=cells1;
	board->numOfEmptyCells=dimension*dimension;
	board->blockHeight=blockHeight;
	board->blockWidth=blockWidth;

	solution = cpyBoard(board, solution);

	randomizeBackTracking(solution, solution);

	board->solution=cpyCellArray(solution->cells, dimension*dimension);

	while(i<numberOfCellsToFill)
	{
		randX=rand()%dimension;
		randY=rand()%dimension;
		if (!board->cells[cellNum(board, randX, randY)].isFixed)
		{
			board->cells[cellNum(board, randX, randY)]=
					solution->cells[cellNum(board, randX, randY)];
			board->cells[cellNum(board, randX, randY)].isFixed=1;
			board->numOfEmptyCells--;
			i++;
		}
	}

	//TODO: check if this isn't wrong
	free(solution->cells);
	free(solution);

	printBoard(board);

	return board;
}

Board* initGame(int dimension, int blockHeight, int blockWidth)
{
	int input;
	int numberOfCellsToFill;
	printf("Please enter the number of cells to fill [0-80]:\n");

	input = scanf("%d", &numberOfCellsToFill);
//	numberOfCellsToFill=75;

	if(input == EOF)
	{
		printf("Exiting...\n");
		exit(0);
	}

	while((numberOfCellsToFill<0 || numberOfCellsToFill>80) && input!=EOF)
	{
		printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		input = scanf("%d", &numberOfCellsToFill);
	}

	if(input == EOF)
	{
		printf("Exiting...\n");
		exit(0);
	}

	return initGameWithNumberOfCellsToFill(dimension, blockHeight, blockWidth,numberOfCellsToFill);

}

Board* restart(Board *board) {
	int rows = board->rows, blockHeight = board->blockHeight, blockWidth = board->blockWidth;
	freeBoard(board);
	return initGame(rows, blockHeight, blockWidth);
}

int isGameOver(Board *board) {
	return board->numOfEmptyCells == 0;
}
