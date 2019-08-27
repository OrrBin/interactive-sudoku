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
		printf("invalid undo. first move");
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
	*currentMove=(*currentMove)->next;
	return 1;
}

void cancelSingleMove(Board *board, Move *move)
{
	setValueOfCell(board, move->row, move->col, move->previousValue);
}

void redoSingleMove(Board *board, Move *move)
{
	setValueOfCell(board, move->row, move->col, move->newValue);
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
}
