/*
 * types.h
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#ifndef TYPES_H_
#define TYPES_H_



#endif /* TYPES_H_ */

typedef struct Cells
{
	int value;
	int isFixed;
}Cell;

typedef struct Boards
{
	int rows;
	int cols;
	Cell* cells ;
	int numOfEmptyCells;
	int blockHeight;
	int blockWidth;
}Board;
