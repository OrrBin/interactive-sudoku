/*
 * util.h
 *
 *  Created on: May 23, 2019
 *      Author: orrbo
 */

#ifndef UTIL_H_
#define UTIL_H_



#endif /* UTIL_H_ */

#include "types.h"

/*
 * printing a board
 */
void printBoard(Board* board);

/*
 * returns a pointer to array in length numOfValidValues,
 * where array[i]=i;
 */
int *createRange(int numOfValidValues, int *validIndexes);


int *removeAtIndex(int *array, int size, int idx);

/*
 * gets board, row and col.
 * returns the position in the one dimension
 * array of row,col.
 */
int cellNum(Board* board, int row, int col);

/*
 * returns the row of a cell in
 * the one dimension array of board
 */
int cellRow(Board* board, int cellNum);

/*
 * returns the col of a cell in
 * the one dimension array of board
 */
int cellCol(Board* board, int cellNum);

/*
 * copy the content of *board to *destination
 */
Board* cpyBoard(Board* board, Board* destination);

/*
 * copy the content of *src and returns
 * a pointer to this content
 */
Cell *cpyCellArray(Cell *src, int size);


Board *cpyBoardAsFixed(Board* board, Board* destination);

/*
 * checks whether or not cell fixed.
 */
int isCellFixed(Board* board, int row, int col);

/*
 * checks if board[row][col] is the last cell in the board
 */
int isLastCell(Board* board, int row, int col);


int isLastCellInRow(Board* board, int col);

/*
 * free the memoery of *board
 */
void freeBoard(Board *board);

/*
 * checks whether or not string1 equal to string2
 */
int isStringsEqual(char *string1, char *string2);

/*
 * read input from user
 */
void getStringFromUser();
