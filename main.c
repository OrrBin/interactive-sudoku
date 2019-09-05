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
#include "board_reader.h"
#include "game.h"
#include "game_manager.h"
#include "stack.h"
#include "move.h"
#include "board_writer.h"

/*
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

	int i=5;
	int *x;

	struct Stack *stack;
	stack = createStack();
	printf("%d\n" ,isEmpty(stack));
	push(stack, &i);
	printf("%d" ,isEmpty(stack));
	x=(int*) pop(stack);
	printf("%d", *x);
	return 0;*/

/*	Board* board; */
int main() {

	Board* board;
	gll_t *moveList;
	gll_node_t *curr;
	Move *first = NULL;



	SP_BUFF_SET()
	moveList = gll_init();





	gll_pushBack(moveList, first);
	curr=moveList->first;


	board = initEmptyBoard(9, 3, 3);
	printf("start game by entering solve command or edit command\n");
	while (1) {
		playTurn(&board, moveList, &curr);
	}

	return 0;
}
