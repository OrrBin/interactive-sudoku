/*
 * parser.c
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "game.h"

enum mode { INIT, SOLVE, EDIT  };

enum mode currentGameMode = SOLVE;

char *modeToName(enum mode aMode) {
	switch(aMode) {
	case INIT: return "Init";
	case SOLVE: return "Solve";
	case EDIT: return "Edit";
	default: return "Init";
	}
}

void printFormatSolveFileRequired(int isArgSpecified) {
	if(!isArgSpecified) {
		printf("solve command requires one argument: file path. missing argument\n");
	}
	else {
		printf("solve command requires only one argument: file path. too many arguments specified\n");
	}
}

void printFormatSaveFileRequired(int isArgSpecified) {
	if(!isArgSpecified) {
		printf("save command requires one argument: file path. missing argument\n");
	}
	else {
		printf("save command requires only one argument: file path. too many arguments specified\n");
	}
}

void printFormatGuessThresholdRequired(int isArgSpecified) {
	if(!isArgSpecified) {
		printf("guess command requires one argument: threshold. missing argument\n");
	}
	else {
		printf("guess command requires only one argument: threshold. too many arguments specified\n");
	}
}

void printFormatEditTooManyArg() {
	printf("edit command requires only one optional argument: file path\n. too many arguments specified\n");
}

void printFormatMarkErrorsNoArg() {
	printf("mark_erros command requires one argument: 0 or 1\n. missing argument");
}

void printFormatMarkErrorsTooManyArg() {
	printf("mark_erros command requires only one argument: 0 or 1. too many arguments specified\n");
}

void printFormatMarkErrorsWrongArg() {
	printf("mark_erros command requires one argument: 0 or 1. got argument with wrong format\n");
}

void printFormatSetTooManyArg() {
	printf("set command requires only 3 arguments: col row val. too many arguments specified\n");
}

void printFormatSetTooLittleArg() {
	printf("set command requires 3 arguments: col row val. missing arguments\n");
}

void printFormatRowColTooManyArg(char *command) {
	printf("%s command requires only 2 arguments: col row. too many arguments specified\n", command);
}

void printFormatRowColLittleArg(char *command) {
	printf("%s command requires 2 arguments: col row. missing arguments\n", command);
}

void printFormatGenerateTooManyArg() {
	printf("generate command requires only 2 arguments: X Y. too many arguments specified\n");
}

void printFormatGenerateTooLittleArg() {
	printf("generate command requires 2 arguments: X Y. missing arguments\n");
}

void printFormatCommandGetsNoArgs(char *command) {
	printf("%s command gets no arguments", command);
}

void printInvalidMode(char *command, enum mode *validModes, int numOfValidModes) {
	char validModesString[100], *tmpString;
	int idx;

	char *currentModeString = modeToName(currentGameMode);

	tmpString = modeToName(validModes[0]);
	strcpy(validModesString, tmpString);
	for(idx = 1; idx < numOfValidModes; idx++) {
		tmpString = modeToName(validModes[idx]);
		strcat(validModesString, ", ");
		strcat(validModesString, tmpString);
	}
	printf("the command %s is only valid in %s modes. current game mode is %s\n", command, validModesString, currentModeString);
}

void printInvalidCmd() {
	printf("Error: invalid command\n");
}

void printGameOver() {
	printf("Puzzle solved successfully\n");
}

void handleCommandSolve(char *filePath) {
	printf("handle solve file path: %s\n", filePath);

}

void handleCommandEdit(char *filePath) {
	printf("handle edit file path: %s\n", filePath);
}

void handleCommandmarkErrors(int value) {
	printf("handle mark errors value: %d\n", value);
}

void handleCommandPrintBoard() {

}

void handleCommandSet(Board *board, int row, int col, int val) {

	int isGameOverFlag, setCellResult;
	if (val == 0)
		setCellResult = clearCell(board, row - 1, col - 1);
	else {
		setCellResult = setValueOfCell(board, row - 1, col - 1, val);

		isGameOverFlag = isGameOver(board);
		if(isGameOverFlag) {
			printBoard(board);
			printGameOver();
		}
	}

	if(!isGameOverFlag && setCellResult)
		printBoard(board);
}

void handleCommandValidate(Board *board) {
	validate(board);
}

void handleCommandGuess(float threshold) {
	printf("handle guess threshold: %f\n", threshold);
}

void handleCommandGenerate(int x, int y) {
	printf("handle generate x: %d, y: %d\n", x, y);
}

void handleCommandUndo() {

}

void handleCommandRedo() {

}

void handleCommandSave(char *filePath) {
	printf("handle save file path: %s\n", filePath);
}

void handleCommandHint(Board *board, int row, int col) {
	hint(board, row - 1, col - 1);
}

void handleCommandGuessHint(Board *board, int row, int col) {
	printf("handle guess hint board: %s, row: %d, col: %d\n", board, row, col);
}

void handleCommandNumSolutions(Board *board) {
	int numOfSolutions;
	numOfSolutions = findNumberOFSolutions(board);

	printf("Current board has %d solutions\n", numOfSolutions);
}

void handleCommandAutoFill() {

}

void handleCommandReset() {

}

void handleCommandExit(Board *board) {
	exitGame(board);
}

void parseCommand(Board **boardP, char* command) {
	char *firstArg, *secondArg, *thirdArg, *forthArg;
	int firstIntArg, secondIntArg, thirdIntArg, isGameOverFlag;
	float threshold;
	char *token;
	Board *board = *boardP;
	enum mode validModes[3];

	isGameOverFlag = isGameOver(board);
	token = strtok(command, " \t\r\n");

	if (token == NULL) {
		return;
	}

	firstArg = strtok(NULL, " \t\r\n");
	secondArg = strtok(NULL, " \t\r\n");
	thirdArg = strtok(NULL, " \t\r\n");
	forthArg = strtok(NULL, " \t\r\n");


	if (isStringsEqual(token, "solve")) {
		if(firstArg == NULL) {
			printFormatSolveFileRequired(0);
			return;
		}

		if(secondArg != NULL) {
			printFormatSolveFileRequired(1);
			return;
		}

		handleCommandSolve(firstArg);
	}

	else if (isStringsEqual(token, "edit")) {
		if(secondArg != NULL) {
			printFormatEditTooManyArg();
			return;
		}

		handleCommandEdit(firstArg);
	}

	else if (isStringsEqual(token, "mark_errors")) {
		if(firstArg == NULL) {
			printFormatMarkErrorsNoArg();
			return;
		}

		if(secondArg != NULL) {
			printFormatMarkErrorsTooManyArg();
			return;
		}

		firstIntArg = atoi(firstArg);

		if(firstIntArg != 0 && firstIntArg != 1) {
			printFormatMarkErrorsWrongArg();
			return;
		}


		if(currentGameMode != SOLVE) {
			validModes[0] = SOLVE ;
			printInvalidMode(token, validModes, 1);
			return;
		}

		firstIntArg = atoi(firstArg);

		handleCommandmarkErrors(firstIntArg);
	}

	else if (isStringsEqual(token, "print_board")) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		handleCommandPrintBoard();
	}

	else if (isStringsEqual(token, "set") && !isGameOverFlag) {
		if(firstArg == NULL || secondArg == NULL || thirdArg == NULL) {
			printFormatSetTooLittleArg();
			return;
		}

		if(forthArg != NULL) {
			printFormatSetTooManyArg();
			return;
		}


		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		firstIntArg = atoi(firstArg);
		secondIntArg = atoi(secondArg);
		thirdIntArg = atoi(thirdArg);

		handleCommandSet(board, secondIntArg, firstIntArg, thirdIntArg);
	}

	else if (isStringsEqual(token, "validate") && !isGameOverFlag) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		handleCommandValidate(board);
	}


	else if (isStringsEqual(token, "guess")) {
		if(firstArg == NULL) {
			printFormatGuessThresholdRequired(0);
			return;
		}

		if(secondArg != NULL) {
			printFormatGuessThresholdRequired(1);
			return;
		}

		if(currentGameMode != SOLVE) {
			validModes[0] = SOLVE;
			printInvalidMode(token, validModes, 1);
			return;
		}

		threshold = atof(firstArg);

		handleCommandGuess(threshold);
	}

	else if (isStringsEqual(token, "generate")) {
		if(firstArg == NULL || secondArg == NULL) {
			printFormatGenerateTooLittleArg();
			return;
		}

		if(thirdArg != NULL) {
			printFormatGenerateTooManyArg();
			return;
		}

		if(currentGameMode != EDIT) {
			validModes[0] = EDIT;
			printInvalidMode(token, validModes, 1);
			return;
		}

		firstIntArg = atoi(firstArg);
		secondIntArg = atoi(secondArg);

		handleCommandGenerate(firstIntArg, secondIntArg);
	}

	else if (isStringsEqual(token, "undo")) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}


		handleCommandUndo();
	}

	else if (isStringsEqual(token, "redo")) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}


		handleCommandRedo();
	}

	else if (isStringsEqual(token, "save")) {
		if(firstArg == NULL) {
			printFormatSaveFileRequired(0);
			return;
		}

		if(secondArg != NULL) {
			printFormatSaveFileRequired(1);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		handleCommandSave(firstArg);
	}

	else if (isStringsEqual(token, "hint") && !isGameOverFlag) {
		if(firstArg == NULL || secondArg == NULL) {
			printFormatRowColLittleArg(token);
			return;
		}

		if(thirdArg != NULL) {
			printFormatRowColTooManyArg(token);
			return;
		}

		if(currentGameMode != SOLVE) {
			validModes[0] = SOLVE;
			printInvalidMode(token, validModes, 1);
			return;
		}

		firstIntArg = atoi(firstArg);
		secondIntArg = atoi(secondArg);

		handleCommandHint(board, secondIntArg, firstIntArg);
	}

	else if (isStringsEqual(token, "guess_hint") && !isGameOverFlag) {
		if(firstArg == NULL || secondArg == NULL) {
			printFormatRowColLittleArg(token);
			return;
		}

		if(thirdArg != NULL) {
			printFormatRowColTooManyArg(token);
			return;
		}

		if(currentGameMode != SOLVE) {
			validModes[0] = SOLVE;
			printInvalidMode(token, validModes, 1);
			return;
		}

		firstIntArg = atoi(firstArg);
		secondIntArg = atoi(secondArg);

		handleCommandGuessHint(board, secondIntArg, firstIntArg);
	}

	else if (isStringsEqual(token, "num_solutions") && !isGameOverFlag) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		handleCommandNumSolutions(board);
	}

	else if (isStringsEqual(token, "autofill") && !isGameOverFlag) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != SOLVE) {
			validModes[0] = SOLVE;
			printInvalidMode(token, validModes, 1);
			return;
		}

		/* handle command */

		handleCommandAutoFill();
	}


	else if (isStringsEqual(token, "reset") && !isGameOverFlag) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		if(currentGameMode != EDIT && currentGameMode != SOLVE) {
			validModes[0] = EDIT;
			validModes[1] = SOLVE;
			printInvalidMode(token, validModes, 2);
			return;
		}

		handleCommandReset();
	}

	/* there is reset instead */
	else if (isStringsEqual(token, "restart")) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}

		*boardP = restart(board);
	}

	else if (isStringsEqual(token, "exit")) {
		if(firstArg != NULL) {
			printFormatCommandGetsNoArgs(token);
			return;
		}


		handleCommandExit(board);
	}

	else {
		printInvalidCmd();
	}

}


