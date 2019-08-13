/*
 * parser.h
 *
 *  Created on: 22 ���� 2019
 *      Author: yarden.flori
 */

#ifndef PARSER_H_
#define PARSER_H_



#include <stdio.h>
#include <string.h>


/*
 * parseCommand gets from user command, and
 * determine which command it is.
 * after that, it calls to the relevant function
 * to execute the command, or print error of invalid
 * command.
 */
void parseCommand(Board **boardP, char *command);

#endif /* PARSER_H_ */
