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
	if(list->size==0)
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
	if(list->size==0)
	{
		printf("invalid redo. last move");
		return 0;
	}

	move = (Move*) (*currentMove)->data;

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
	setValueOfCell(board, move->col, move->row, move->previousValue);
}

void redoSingleMove(Board *board, Move *move)
{
	setValueOfCell(board, move->col, move->row, move->newValue);
}
