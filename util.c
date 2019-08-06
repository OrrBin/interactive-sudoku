/*
 * util.c
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int cellNum(Board* board, int row, int col) {
	return row * (board->dimension) + col;
}

int cellRow(Board* board, int cellNum) {
	return cellNum / (board->dimension);
}

int cellCol(Board* board, int cellNum) {
	return cellNum % (board->dimension);
}

int *createRange(int numOfValidValues, int *validIndexes) {
	int idx;
	validIndexes = (int *) malloc(numOfValidValues * sizeof(int));
	for (idx = 0; idx < numOfValidValues; idx++) {
		validIndexes[idx] = idx;
	}

	return validIndexes;
}

int *removeAtIndex(int *array, int size, int idx) {
	int* temp = malloc((size - 1) * sizeof(int));
	if (idx != 0)
		memcpy(temp, array, idx * sizeof(int));

	if (idx != (size - 1))
		memcpy(temp + idx, array + idx + 1, (size - idx - 1) * sizeof(int));

	free(array);
	return temp;
}


int isCellFixed(Board* board, int row, int col) {
	return board->cells[cellNum(board, row, col)].isFixed;
}

int isCellEmpty(Board* board, int row, int col) {
	return board->cells[cellNum(board, row, col)].value == 0;
}

Board *cpyBoardImpl(Board* board, Board* destination, int asFixed) {
	int i;
	Cell *cells;
	cells = (Cell*) malloc((board->dimension * board->dimension) * sizeof(Cell));
	if (cells == NULL) {
		printf("ERROR in malloc cells\n");
	}
	for (i = 0; i < board->dimension * board->dimension; i++) {
		cells[i].value = board->cells[i].value;

		if (asFixed && cells[i].value != 0)
			cells[i].isFixed = 1;
		else
			cells[i].isFixed = board->cells[i].isFixed;
	}
	destination->dimension = board->dimension;
	destination->numOfEmptyCells = board->numOfEmptyCells;
	destination->cells = cells;
	destination->blockHeight = board->blockHeight;
	destination->blockWidth = board->blockWidth;

	return destination;
}

Board *cpyBoard(Board* board, Board* destination) {
	return cpyBoardImpl(board, destination, 0);
}

Cell *cpyCellArray(Cell *src, int size) {
	Cell * p = (Cell *) malloc(size * sizeof(Cell));
	memcpy(p, src, size * sizeof(Cell));
	return p;
}

Board *cpyBoardAsFixed(Board* board, Board* destination) {
	return cpyBoardImpl(board, destination, 1);
}

int isLastCell(Board* board, int row, int col) {
	return cellNum(board, row, col) == (board->dimension) * (board->dimension) - 1;
}

int isLastCellInRow(Board* board, int col) {
	return col == board->dimension - 1;
}

void freeBoard(Board *board) {
	if (board != NULL) {
		if (board->cells != NULL)
			free(board->cells);
		if (board->solution != NULL)
			free(board->solution);
		free(board);
	}
}

int isStringsEqual(char *string1, char *string2) {
	return strcmp(string1, string2) == 0;
}

char *getStringFromUser(char *cmd) {
	return fgets(cmd, MAX_CHARS_IN_COMMAND, stdin);
}

void printBoard(Board *board) {
	int i, j;

	printf("----------------------------------\n");
	for (i = 0; i < board->dimension; i++) {
		printf("| ");
		for (j = 0; j < board->dimension; j++) {

			if (isCellFixed(board, i, j)) {
				if (isCellEmpty(board, i, j))
					printf(".  ");
				else
					printf(".%d ", board->cells[cellNum(board, i, j)].value);
			} else {
				if (isCellEmpty(board, i, j))
					printf("   ");
				else
					printf(" %d ", board->cells[cellNum(board, i, j)].value);
			}
			if ((j + 1) % (board->blockWidth) == 0) {
				printf("|");
				if(j < board->dimension - 1)
					printf(" ");
			}

		}
		printf("\n");
		if ((i + 1) % (board->blockHeight) == 0)
			printf("----------------------------------\n");

	}
}
