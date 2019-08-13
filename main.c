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
#include "move.h"

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
int main(int argc, char* argv[]) {

	Board* board;
		int seed = atoi(argv[1]);


	gll_node_t *node;

	Move *m1 = (Move*) malloc(sizeof(Move));
	Move *m2 = (Move*) malloc(sizeof(Move));
	Move *m3 = (Move*) malloc(sizeof(Move));
	Move *m4 = (Move*) malloc(sizeof(Move));
	Move *m5 = (Move*) malloc(sizeof(Move));
	Move *m6 = (Move*) malloc(sizeof(Move));
	gll_t *list;
	m1->col=1;
	m2->col=2;
	m3->col=3;
	m4->col=4;
	m5->col=5;
	m6->col=6;

	list = gll_init();
	gll_add(list, m1, 0);
	gll_add(list, m2, 1);
	gll_add(list, m3, 2);
	gll_add(list, m4, 3);
	gll_add(list, m5, 4);
	gll_add(list, m6, 5);

	node = list->first->next->next;


	remove_all_from_curr(list, node);

	printf("%d", ((Move*) list->first->data)->col);


	srand(seed);



	SP_BUFF_SET();
	setbuf(stdout, NULL);

	if (argc < 1) {
		exit(-1);
	}

	board = initGame(1);

	parseCommand(&board, "solve 123");
	while (1) {
		playTurn(&board);
	}


	return 0;
}
