/*
 * types.h
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#include "gll.h"

#ifndef TYPES_H_
#define TYPES_H_


#define MAX_CHARS_IN_COMMAND 1024

enum mode { INIT, SOLVE, EDIT  };

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


typedef struct LPSol {
	int dimension;
	enum boolean solutionFound;
	gll_t **varIndexes;
	double *foundSolution;
} LPSol;

typedef struct intTuple2 {
	int item1;
	int item2;
} intTuple2;

#endif /* TYPES_H_ */
