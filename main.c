/*
 * main.c
 *
 *  Created on: Apr 26, 2019
 *      Author: orrbo
 */
#include <stdio.h>
#include <stdlib.h>

#include "main_aux.h"
#include "SPBufferset.h"
#include  "util.h"
#include "solver.h"

int main() {

	int i, j, isSuccess;
	Cell *cells;
	Board *result = (Board *) malloc(sizeof(Board));
	Board *board = (Board *) malloc(sizeof(Board));
	;
	SP_BUFF_SET()
	;
	printf("start of main\n");

	cells = (Cell *) malloc((81) * sizeof(Cell));
	for (i = 0; i < 81; i++) {
//		if(i == 0) {
//			cells[i].value = 9;
//			cells[i].isFixed = 1;
//		}
//		else if(i == 4) {
//			cells[i].value = 8;
//			cells[i].isFixed = 1;
//		}
//		else {
		cells[i].value = 0;
		cells[i].isFixed = 0;
//		}
	}

	printf("after init cells\n");

	board->cols = 9;
	board->rows = 9;
	board->cells = cells;
	board->numOfEmptyCells = 0;
	board->blockHeight = 3;
	board->blockWidth = 3;

	printf("after init test2\n");

	isSuccess = recursiveBackTracking(board, result);

	if(!isSuccess) {
		printf("NULLLLL");
	}

	printf("after backtracking\n");

	printf("after back tracking\n");

	for (i = 0; i < result->rows; i++) {
		for (j = 0; j < result->rows; j++) {
			printf("%d ", result->cells[cellNum(result, i, j)].value);
		}
		printf("\n");
	}

	freeBoard(result);

}
