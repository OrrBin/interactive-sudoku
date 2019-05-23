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

void parseCommand(Board *board, char* command)
{
	int col, row, val;
	char *token = strtok(command, " ");

	if(isStringsEqual(token, "set"))
	{
		row = atoi (strtok(NULL, " "));
		col = atoi (strtok(NULL, " "));
		val = atoi (strtok(NULL, " "));
		setValueOfCell(board, row, col, val);
	}

	else if(isStringsEqual(token, "hint"))
	{
		row = atoi (strtok(NULL, " "));
		col = atoi (strtok(NULL, " "));
		hint(board, row, col);
	}

	else if(isStringsEqual(token, "validate"))
	{
		validate(board);
	}

	else if(isStringsEqual(token, "restart"))
	{
		restart(board);
	}


	else if(isStringsEqual(token, "exit"))
	{
		exitGame(board);
	}

}
