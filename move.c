/*
 * move.c
 *
 *  Created on: 12 Aug 2019
 *      Author: Yarden
 */

#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include "gll.h"
#include "types.h"
#include "game.h"

int undo(Board *board, gll_t* list, gll_node_t **currentMove)
{
	Move *move;
	if(list->size==1 || list->first==*currentMove)
	{
		printf("invalid undo. first move\n");
		return 0;
	}


	move = (Move*) (*currentMove)->data;

	while(move->isFirstMoveOfCommand==0)
	{
		cancelSingleMove(board, move);
		*currentMove=(*currentMove)->prev;
		move = (Move*) (*currentMove)->data;
	}

	cancelSingleMove(board, move);
	*currentMove=(*currentMove)->prev;
	return 1;
}

int redo(Board *board, gll_t* list, gll_node_t **currentMove)
{

	Move *move;
	if(list->size==1)
	{
		printf("invalid redo. no moves\n");
		return 0;
	}
	if((*currentMove)->next==NULL)
	{
		printf("invalid redo. last move\n");
		return 0;
	}

	move = (Move*) (*currentMove)->next->data;

	while(move->isLastMoveOfCommand==0)
	{
		redoSingleMove(board, move);
		*currentMove=(*currentMove)->next;
		move = (Move*) (*currentMove)->data;
	}
	redoSingleMove(board, move);
	return 1;
}

void cancelSingleMove(Board *board, Move *move)
{
	setValueOfCell(board, move->row, move->col, move->previousValue, SOLVE);
}

void redoSingleMove(Board *board, Move *move)
{
	setValueOfCell(board, move->row, move->col, move->newValue, SOLVE);
}

void addMoveToCurrentAndCleanNextMoves (gll_t* list, gll_node_t **currentMove, Move *move)
{
	gll_remove_all_from_curr(list, *currentMove);
	gll_pushBack(list, move);
}

void printMove(gll_node_t *currentMove)
{
	Move *move;
	move = (Move*) currentMove->data;
	printf("row is %d\ncol is %d\n prev is %d\nnew is %d\nis first? %d\nis last? %d\n",
			move->row, move->col, move->previousValue, move->newValue, move->isFirstMoveOfCommand, move->isLastMoveOfCommand);
	printf("----------");
}

void printMoves(gll_t* moveList, gll_node_t **currentMove)
{
	int i, size;
	gll_node_t *node = (gll_node_t *) malloc(sizeof(gll_node_t));

	size = moveList->size;
	printf("size of list is %d\n", size);
	if (size==1)
		return;
	node = moveList->first->next;
	for(i=1; i<size; i++)
	{
		if(*currentMove==node)
			printf("this is current move:\n");
		printMove(node);
		node=node->next;
	}
}
