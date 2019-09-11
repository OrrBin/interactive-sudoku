/*
 * parser.h
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_



#include <stdio.h>
#include <string.h>
#include "gll.h"
#include "util.h"

/*
 * parseCommand gets from user command, and
 * determine which command it is.
 * after that, it calls to the relevant function
 * to execute the command, or print error of invalid
 * command.
 */
void parseCommand(Board **boardP, char* command, gll_t *moveList, gll_node_t **curr);
void handleCommandSet(Board *board, int row, int col, int val, gll_t *moveList,
	gll_node_t **curr, int isFirstMoveOfCommand, int isLastMoveOfCommand, enum boolean shouldPrint, enum mode currentGameMode) ;
void handleCommandSolve(Board **board, char *filePath, gll_t *moveList, gll_node_t **curr);
void handleCommandEdit(Board **board, char *filePath, gll_t *moveList, gll_node_t **curr);
void handleCommandUndo(Board *board, gll_t* moveList, gll_node_t **curr);
void handleCommandRedo(Board *board, gll_t* moveList, gll_node_t **curr);
void handleCommandAutoFill(Board *board, gll_t *moveList, gll_node_t **curr);
void handleCommandReset(Board *board, gll_t *moveList, gll_node_t **curr);
void handleCommandGuess(Board *board, float threshold, gll_t *moveList, gll_node_t **curr);
void handleCommandGenerate(int x, int y, Board *board, gll_t *moveList, gll_node_t **curr);


#endif /* GAME_MANAGER_H_ */
