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

void parseCommand(Board **boardP, char* command)
{

	int col, row, val;
	char *token = strtok(command, " \t\r\n");
	Board *board = *boardP;

	printf("%s\n", token);
	if(isStringsEqual(token, "set"))
	{
		row = atoi (strtok(NULL, " \t\r\n"));
		col = atoi (strtok(NULL, " \t\r\n"));
		val = atoi (strtok(NULL, " \t\r\n"));

		setValueOfCell(board, row, col, val);
		printBoard(board);
	}

	else if(isStringsEqual(token, "hint"))
	{
		row = atoi (strtok(NULL, " \t\r\n"));
		col = atoi (strtok(NULL, " \t\r\n"));
		hint(board, row, col);
	}

	else if(isStringsEqual(token, "validate"))
	{
		validate(board);
	}

	else if(isStringsEqual(token, "restart"))
	{
		*boardP = restart(board);
	}


	else if(isStringsEqual(token, "exit"))
	{
		exitGame(board);
	}

}
