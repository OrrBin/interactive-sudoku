/*
 * move.h
 *
 *  Created on: 6 Aug 2019
 *      Author: Yarden
 */

#ifndef MOVE_H_
#define MOVE_H_



#endif /* MOVE_H_ */

struct Move {
    enum command{set, autofill, generate, guess};
    int row;
    int col;
    int val;
    int previousVal;
    Board* previousBoard;
}Move;
