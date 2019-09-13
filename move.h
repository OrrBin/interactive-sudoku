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

int undo(Board *board, List* list, ListNode **currentMove);
int redo(Board *board, List* list, ListNode **currentMove);
void cancelSingleMove(Board *board, Move *move);
void redoSingleMove(Board *board, Move *move);
void addMoveToCurrentAndCleanNextMoves (List* list, ListNode **currentMove, Move *move);
void printMove(ListNode *currentMove);
void printMoves(List* moveList, ListNode **currentMove);
void freeMoveList(List *list);
int removeAllMovesFromCurr(List *list, ListNode *current);
#endif /* MOVE_H_ */

