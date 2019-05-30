/*
 * parser.c
 *
 *  Created on: 22 במאי 2019
 *      Author: yarden.flori
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "game.h"

void printInvalidCmd() {
	printf("Error: invalid command\n");
}

void printGameOver() {
	printf("Puzzle solved successfully\n");
}

void parseCommand(Board **boardP, char* command) {

	char *colStr, *rowStr, *valStr;
	int col, row, val, isGameOverFlag, setCellResult;
	char *token;
	Board *board = *boardP;
	isGameOverFlag = isGameOver(board);

	token = strtok(command, " \t\r\n");

	if (token == NULL) {
		return;
	}

	colStr = strtok(NULL, " \t\r\n");
	rowStr = strtok(NULL, " \t\r\n");
	valStr = strtok(NULL, " \t\r\n");

	if(colStr != NULL)
		col = atoi(colStr);
	if(rowStr != NULL)
		row = atoi(rowStr);
	if(valStr != NULL)
		val = atoi(valStr);

	if (isStringsEqual(token, "set") && !isGameOverFlag) {

		if (colStr == NULL || rowStr == NULL || valStr == NULL) {
			printInvalidCmd();
			return;
		}

		if (val == 0)
			setCellResult = clearCell(board, row - 1, col - 1);
		else {
			setCellResult = setValueOfCell(board, row - 1, col - 1, val);

			isGameOverFlag = isGameOver(board);
			if(isGameOverFlag) {
				printGameOver();
			}
		}

		if(!isGameOverFlag && setCellResult)
			printBoard(board);
	}

	else if (isStringsEqual(token, "hint") && !isGameOverFlag) {

		if (colStr == NULL || rowStr == NULL) {
			printInvalidCmd();
			return;
		}

		hint(board, row - 1, col - 1);
	}

	else if (isStringsEqual(token, "validate") && !isGameOverFlag) {
		validate(board);
	}

	else if (isStringsEqual(token, "restart")) {
		*boardP = restart(board);
	}

	else if (isStringsEqual(token, "exit")) {
		exitGame(board);
	}

	else {
		printInvalidCmd();
	}

}


