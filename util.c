/*
 * util.c
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "util.h"


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
	int dimension=board->dimension;
	int blockHeight = board->blockHeight;
	for(i=0 ; i< 4*dimension+blockHeight+1; i++)
	{
		printf("-");
	}
	printf("\n");

	for (i = 0; i < board->dimension; i++) {
		printRow(board, i);
		printf("\n");
		if((i+1)%blockHeight==0)
		{
			for(j=0 ; j< 4*dimension+blockHeight+1; j++)
				{
					printf("-");
				}
				printf("\n");
		}


	}
}

void printCell(Board* board, int i, int j)
{
	int mode=1, markErrors=0;
	if(board->cells[cellNum(board, i, j)].value==0)
		printf("   ");
	else
		printf(" %2d", board->cells[cellNum(board, i, j)].value);

	if(board->cells[cellNum(board, i, j)].isFixed)
		printf(".");
	else if((board->cells[cellNum(board, i, j)].isError) && (markErrors==1 || mode==0))
			printf("*");
	else
		printf(" ");
}

void printRow(Board* board, int row)
{
	int i,j,col=0;
	int blockHeight= board->blockHeight;
	int blockWidth = board->blockWidth;

	printf("|");

	for (i = 0; i < blockHeight; i++) {
			for(j=0; j<blockWidth;j++)
			{
				printCell(board, row, col++);
			}
			printf("|");
		}
}
