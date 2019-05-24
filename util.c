/*
 * util.c
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <string.h>

int cellNum(Board* board, int row, int col) {
	return row * (board->cols) + col;
}

void cpyBoard(Board* board, Board* destination) {
	int i;
	Cell *cells;
	printf("before cells init board rows and cols: %d\n", ((board->rows * board->cols) * sizeof(Cell)));
	cells = (Cell*) malloc((board->rows * board->cols) * sizeof(Cell));
	if(cells == NULL) {
		printf("ERROR in malloc cells\n");
	}
	printf("cells init\n");
	for (i = 0; i < board->rows * board->cols; i++) {
		cells[i].value = board->cells[i].value;
		cells[i].isFixed = board->cells[i].isFixed;
	}
	printf("for cells init");
	destination->rows = board->rows;
	destination->cols = board->cols;
	destination->numOfEmptyCells = board->numOfEmptyCells;
	destination->cells = cells;
	destination->blockHeight = board->blockHeight;
	destination->blockWidth = board->blockWidth;
	printf("destination init");
}

int isCellFixed(Board* board, int row, int col) {
	return board->cells[cellNum(board, row, col)].isFixed;
}

int isLastCell(Board* board, int row, int col) {
	return cellNum(board, row, col) == (board->cols) * (board->rows) - 1;
}

int isLastCellInRow(Board* board, int row, int col) {
	return col == board->cols - 1;
}

void freeBoard(Board *board) {
	free(board->cells);
	free(board);
}

int isStringsEqual(char *string1, char *string2)
{
	return strcmp(string1, string2)==0;
}
