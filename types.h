/*
 * types.h
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#ifndef TYPES_H_
#define TYPES_H_


#define MAX_CHARS_IN_COMMAND 1024

enum boolean {false, true};

/**
 * struct the describes board cell
 */
typedef struct Cells
{
	int value;
	int isFixed;
	int isError;
}Cell;

typedef struct StackCell
{
	int cellNum, value, isFixed;
}StackCell;

/**
 * struct the describes game board
 * cells holds current state of the board
 * solution holds valid solution if the board
 */
typedef struct Boards
{
	int dimension;
	Cell* cells ;
	Cell* solution;

	int numOfEmptyCells;
	int blockHeight;
	int blockWidth;
}Board;




#endif /* TYPES_H_ */
