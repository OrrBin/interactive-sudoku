/*
 * main.c
 *
 *  Created on: Apr 26, 2019
 *      Author: orrbo
 */
#include <stdio.h>
#include <stdlib.h>

#include "SPBufferset.h"
#include  "util.h"
#include "solver.h"
#include "game.h"
#include "parser.h"
#include "stack.h"

int testExhaustiveBackTracking() {
	int result = 0;
	Board *board;
	SP_BUFF_SET()
	;
	board = initGame(3, 3, 1);
	result = exhaustiveBackTracking(board);

	printf("%d", result);
	return 0;
}

int main() {

	return testExhaustiveBackTracking();

	/*int i=5;
	int *x;

	struct Stack *stack;
	stack = createStack();
	printf("%d\n" ,isEmpty(stack));
	push(stack, &i);
	printf("%d" ,isEmpty(stack));
	x=(int*) pop(stack);
	printf("%d", *x);
	return 0;*/

/*	Board* board;
	int seed = atoi(argv[1]);
	srand(seed);

	SP_BUFF_SET()
	;

	setbuf(stdout, NULL);

	if (argc < 1) {
		exit(-1);
	}

	board = initGame(10, 2, 5);

	while (1) {
		playTurn(&board);
	}*/
}
