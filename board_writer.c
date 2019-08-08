/*
 * board_writer.c
 *
 *  Created on: Aug 8, 2019
 *      Author: orrbo
 */
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void writeLineToFile(Board *board, FILE *filePtr, int row) {
	int col;
	for(col = 0; col < board->dimension; col++) {
		fprintf(filePtr, "%d", board->cells[cellNum(board, row, col)].value);
		if(isCellFixed(board, row, col)) {
			fprintf(filePtr, ".");
		}
		if (!isLastCellInRow(board, col)){
			fprintf(filePtr, " ");
		}
	}
}

int writeBoardToFile(Board *board, char *filePath) {
	FILE *filePtr;
	int i;
	filePtr = fopen(filePath, "w");
	if(filePtr == NULL)
	{
		printf("Error: Could not open the given file: %s", filePath);
		return -1;
	}

	fprintf(filePtr,"%d ", board->blockHeight);
	fprintf(filePtr,"%d\n", board->blockWidth);

	for(i = 0; i < board->dimension; i++) {
		writeLineToFile(board, filePtr, i);
		fprintf(filePtr,"\n");
	}

	fclose(filePtr);
	return 0;

}
