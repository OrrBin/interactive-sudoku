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

	char *rowStr, *colStr, *valStr;
	int col, row, val, isGameOverFlag;
	Board *board = *boardP;

	isGameOverFlag = isGameOver(board);

	char *token = strtok(command, " \t\r\n");

	if (token == NULL) {
		return;
	}

	rowStr = strtok(NULL, " \t\r\n");
	colStr = strtok(NULL, " \t\r\n");
	valStr = strtok(NULL, " \t\r\n");

	row = atoi(rowStr);
	col = atoi(colStr);
	val = atoi(valStr);

	if (isStringsEqual(token, "set") && !isGameOverFlag) {
		printf("strings: %s, %s, %s\n", rowStr, colStr, valStr);

		if (rowStr == NULL || colStr == NULL || valStr == NULL) {
			printInvalidCmd();
			return;
		}

		if (val == 0)
			clearCell(board, row - 1, col - 1);
		else {
			setValueOfCell(board, row - 1, col - 1, val);
			isGameOverFlag = isGameOver(board);
			if(isGameOverFlag) {
				printGameOver();
			}
		}

		if(!isGameOverFlag)
			printBoard(board);
	}

	else if (isStringsEqual(token, "hint") && !isGameOverFlag) {

		if (rowStr == NULL || colStr == NULL) {
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


