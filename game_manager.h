/*
 * parser.h
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_



#include <stdio.h>
#include <string.h>
#include "util.h"

/*
 * parseCommand gets from user command, and
 * determine which command it is.
 * after that, it calls to the relevant function
 * to execute the command, or print error of invalid
 * command.
 */
void parseCommand(Board **boardP, char *command);

#endif /* GAME_MANAGER_H_ */
