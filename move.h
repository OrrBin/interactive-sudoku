/*
 * move.h
 *
 *  Created on: 6 Aug 2019
 *      Author: Yarden
 */

#include "types.h"

#ifndef MOVE_H_
#define MOVE_H_

typedef struct Moves
{
	int isFirstMoveOfCommand;
	int isLastMoveOfCommand;
	int col;
	int row;
	int previousValue;
	int newValue;
}Move;

int undo(Board *board, gll_t* list, gll_node_t **currentMove);
int redo(Board *board, gll_t* list, gll_node_t **currentMove);
void cancelSingleMove(Board *board, Move *move);
void redoSingleMove(Board *board, Move *move);
void addMoveToCurrentAndCleanNextMoves (gll_t* list, gll_node_t **currentMove, Move *move);
void printMove(gll_node_t *currentMove);
void printMoves(gll_t* moveList, gll_node_t **currentMove);

#endif /* MOVE_H_ */

