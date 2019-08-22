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
#include "gll.h"
#include "move.h"


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

	if(value == 0) {
		return true;
	}
	valid = validateBlock(board, row, col, value)
									&& validateRow(board, row, col, value)
									&& validateCol(board, row, col, value);

	return valid;
}


int findErrors(Board *board) {
	int i;
	enum boolean result = false;
	for(i = 0; i < (board->dimension)*(board->dimension); i++) {
		if(!validateValue(board, cellRow(board, i), cellCol(board, i), board->cells[i].value)) {
			board->cells[i].isError = true;
			result = true;
		}
	}

	return result;
}

int setValueOfCell(Board *board, int row, int col, int value) {

	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
		return 0;
	}

	board->cells[cellNum(board, row, col)].value = value;
	board->cells[cellNum(board, row, col)].isFixed = false;
	board->numOfEmptyCells--;

	if (validateValue(board, row, col, value)) {
		board->cells[cellNum(board, row, col)].isError = false;
	} else {
		board->cells[cellNum(board, row, col)].isError = true;
		findErrors(board);
	}

	return 1;
}

int clearCell(Board *board, int row, int col) {
	if (board->cells[cellNum(board, row, col)].isFixed) {
		printf("Error: cell is fixed\n");
		return 0;
	}

	board->cells[cellNum(board, row, col)].value = 0;
	board->cells[cellNum(board, row, col)].isError = false;
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

void playTurn(Board **boardP, gll_t *moveList, gll_node_t **curr) {
	char *result;
	char cmd[MAX_CHARS_IN_COMMAND];
	result = getStringFromUser(cmd);
	if (!result) {
		printf("Exiting...\n");
		freeBoard(*boardP);
		exit(1);
	}
	parseCommand(boardP, cmd, moveList, curr);
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
		cells1[i].isError = 0;
		cells2[i].value = 0;
		cells2[i].isFixed = 0;
		cells2[i].isError = 0;
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

	printBoard(board, 1, EDIT);

	return board;
}

Board* initGame(int test) {
	int inputBlockHeight=-10, inputBlockWidth = -10, inputNumberOfCellsToFill=-10;
	int numberOfCellsToFill = -1,blockHeight=-1, blockWidth=-1;
	int dimension;

	printf("Please enter the block height:\n");
	if(test==1)
	{
		blockHeight=3;
		inputBlockHeight=1;
		printf("block height is %d:\n", blockHeight);
	}
	else
		inputBlockHeight = scanf("%d", &blockHeight);



	while((inputBlockHeight!=1 && inputBlockHeight!=EOF)
			|| (blockHeight<1 && inputBlockHeight!=EOF))
	{
		printf("Please enter valid block height:\n");
		while ((getchar()) != '\n');
		inputBlockHeight = scanf("%d", &blockHeight);
	}


	if(test==0)
		while ((getchar()) != '\n');

	printf("Please enter the block width:\n");

	if(test==1)
	{

		blockWidth=4;
		inputBlockWidth=1;
		printf("block width is %d:\n", blockWidth);
	}
	else
		inputBlockWidth = scanf("%d", &blockWidth);

	while((inputBlockWidth!=1 && inputBlockWidth!=EOF)
			|| (blockWidth<1 && inputBlockWidth!=EOF))
	{
		printf("Please enter valid block width:\n");
		while ((getchar()) != '\n');
		inputBlockWidth = scanf("%d", &blockWidth);
	}

	dimension=blockHeight*blockWidth;

	if(test==0)
		while ((getchar()) != '\n');

	printf("Please enter the number of cells to fill [0-%d]:\n", dimension*dimension-1);
	if(test==1)
	{
		numberOfCellsToFill=143;
		inputNumberOfCellsToFill=1;
		printf("number of cells is %d:\n", numberOfCellsToFill);
	}
	else
		inputNumberOfCellsToFill = scanf("%d", &numberOfCellsToFill);


	if (inputNumberOfCellsToFill == EOF || inputBlockHeight==EOF || inputBlockWidth == EOF) {
		printf("Exiting...\n");
		exit(0);
	}

	while ((numberOfCellsToFill < 0 || numberOfCellsToFill > dimension*dimension - 1) && inputNumberOfCellsToFill != EOF) {
		printf(
				"Error: invalid number of cells to fill (should be between 0 and %d)\n",dimension*dimension-1);
		printf("Please enter the number of cells to fill [0-%d]:\n", dimension*dimension-1);
		while ((getchar()) != '\n');
		inputNumberOfCellsToFill = scanf("%d", &numberOfCellsToFill);
	}

	if (inputNumberOfCellsToFill == EOF) {
		printf("Exiting...\n");
		exit(0);
	}

	return initGameWithNumberOfCellsToFill(dimension, blockHeight, blockWidth,
			numberOfCellsToFill);

}

int findNumberOFSolutions(Board *board) {
	return exhaustiveBackTracking(board);
}

void autoFillBoard(Board *board, gll_t *moveList, gll_node_t **curr, enum boolean doPrint) {
	int i, *validValue, row, col;
	int isFirstMoveOfCommand, isLastMoveOfCommand;

	Board *tmp = (Board *) malloc(sizeof(Board));
	isFirstMoveOfCommand=1;
	isLastMoveOfCommand=0;
	cpyBoardAsFixed(board, tmp);
	for(i = 0; i < (board-> dimension) * (board-> dimension); i++) {
		row = cellRow(board, i);
		col = cellCol(board, i);
		if(checkValidValuesNum(tmp,row, col) == 1 && !isCellFixed(tmp, row, col)) {
			validValue = checkValidValues(tmp,row , col);
			handleCommandSet(board, row, col, validValue[0], moveList, curr, isFirstMoveOfCommand, isLastMoveOfCommand);
			if (isFirstMoveOfCommand==1)
			{
				isFirstMoveOfCommand=0;
			}
			if(doPrint) {
				printf("Auto filled cell (%d,%d) to %d\n", col+1, row+1, validValue[0]);
			}
		}
	}

	(((Move*) moveList->last->data)->isLastMoveOfCommand)=1;

	freeBoard(tmp);
	free(validValue);
}

Board* restart(Board *board) {
	freeBoard(board);
	return initGame(0);
}

int isGameOver(Board *board) {

	int i,dimension;
	dimension=board->dimension;

	if(board->numOfEmptyCells!=0)
		return 0;

	for(i=0; i<dimension*dimension; i++)
	{
		if(board->cells[i].isError==1)
			return 0;
	}

	return 1;
}
