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
#include "game.h"
#include "parser.h"

int main() {
	int i;
	int seed = 11;
	Board* board;
	SP_BUFF_SET();
	setbuf(stdout, NULL);

	srand(seed);

	board = initGame(9, 3, 3);

	while(1) {
		playTurn(&board);
	}

	Cell *cells;

	SP_BUFF_SET()
	;

	board->cols = 9;
	board->rows = 9;
	board->numOfEmptyCells = 0;
	board->blockHeight = 3;
	board->blockWidth = 3;


	cells = (Cell *) malloc((81) * sizeof(Cell));
	for (i = 0; i < 81; i++) {
		cells[i].value = 0;
		cells[i].isFixed = 0;

		if (cellRow(board, i) == cellCol(board, i)
				&& cellRow(board, i) % 3 == 0) {
			printf("EQUALS");
			cells[i].value = 1;
			cells[i].isFixed = 1;
		}
	}
	board->cells = cells;

	printBoard(board);
	validate(board);

//	recursiveBackTracking(board, result);
//	randomizeBackTracking(board, result);
//
//
//	printBoard(result);
//
//	freeBoard(result);
//	freeBoard(board);

}
