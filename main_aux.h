/*
 * main_aux.h
 *
 *  Created on: Apr 26, 2019
 *      Author: orrbo
 */

#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_



#endif /* MAIN_AUX_H_ */

/**
 * Evaluates player turn
 * return -1 if an error has occurred
 */
int player_turn(int heaps_arr[], int heaps_num);

/**
 * Initiates the game. gets heap sizes from user and fill
 * the heaps_arr.
 * returns the number of heaps provided by the user (always positive)
 * or -1 if an error occurred
 */
int init_game(int heaps_arr[]);

/**
 * Returns 1 if move is valid according to the Nim game rules
 * and 0 otherwise
 */
int is_valid_move(int heap_num, int num);

/**
 * Prints the current game board
 */
void print_board(int heaps_arr[], int heaps_num, int turn_num);

/**
 * prints game lost message if is_player_won is 0
 * or game won otherwise
 */
void print_game_over(int is_player_won);
