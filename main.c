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
	int seed = 11;
	Board* board;
	SP_BUFF_SET();
	setbuf(stdout, NULL);

	srand(seed);

	board = initGame(9, 3, 3);

	while(1) {
		playTurn(&board);
	}
}
