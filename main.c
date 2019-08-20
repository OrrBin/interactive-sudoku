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
int main(int argc, char* argv[]) {

	Board* board;
	int seed;
	gll_t *moveList;
	gll_node_t *curr;

	SP_BUFF_SET()
	printf("%d", argc);
	board=NULL;

	moveList = gll_init();
	curr=moveList->first;
	seed = atoi(argv[1]);



	while (1)
	{
		playTurn(&board, moveList, &curr);
	}

	/*
	Move *m1, *m2, *m3, *m4, *m5;



	gll_t *list;
	gll_node_t *node;

	list = gll_init();

	board = initGame(1);

	m1 = malloc(sizeof(Move));
	m2 = malloc(sizeof(Move));
	m3 = malloc(sizeof(Move));
	m4 = malloc(sizeof(Move));
	m5 = malloc(sizeof(Move));

	setValueOfCell(board, 2, 1, 1);
	setValueOfCell(board, 3, 1, 2);
	setValueOfCell(board, 2, 4, 3);
	setValueOfCell(board, 3, 4, 4);
	setValueOfCell(board, 5, 5, 5);
	setValueOfCell(board, 2, 1, 6);
	setValueOfCell(board, 3, 1, 7);
	setValueOfCell(board, 2, 4, 8);
	setValueOfCell(board, 3, 4, 9);
	setValueOfCell(board, 5, 5, 10);

	m1->col=1;
	m1->row=2;
	m1->isFirstMoveOfCommand=1;
	m1->isLastMoveOfCommand=1;
	m1->previousValue=1;
	m1->newValue=6;

	m2->col=1;
	m2->row=3;
	m2->isFirstMoveOfCommand=1;
	m2->isLastMoveOfCommand=1;
	m2->previousValue=2;
	m2->newValue=7;

	m3->col=4;
	m3->row=2;
	m3->isFirstMoveOfCommand=1;
	m3->isLastMoveOfCommand=0;
	m3->previousValue=3;
	m3->newValue=8;

	m4->col=4;
	m4->row=3;
	m4->isFirstMoveOfCommand=0;
	m4->isLastMoveOfCommand=1;
	m4->previousValue=4;
	m4->newValue=9;

	m5->col=5;
	m5->row=5;
	m5->isFirstMoveOfCommand=1;
	m5->isLastMoveOfCommand=1;
	m5->previousValue=5;
	m5->newValue=10;

	gll_pushBack(list, m1);
	gll_pushBack(list, m2);
	gll_pushBack(list, m3);
	gll_pushBack(list, m4);
	gll_pushBack(list, m5);


	printf("zzzzzzzzzzzzzzzzzzzzzzzzzz\n");
	printBoard(board);
	printf("zzzzzzzzzzzzzzzzzzzzzzzzzz\n");

	node = list->first->next->next->next->next;

	undo(board, list, &node);
	printf("undo\n");
	printBoard(board);

	undo(board, list, &node);
	printf("undo\n");
	printBoard(board);

	printf("redo\n");
	redo(board, list, &node);
	printBoard(board);




	printf("%d %d %d %d %d %d %d", list->size, m1->col, m2->col, m3->col, m4->col, m5->col, (int) sizeof(node));

*/
	srand(seed);







	return 0;
}
