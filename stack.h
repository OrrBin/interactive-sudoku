/*
 * stack.h
 *
 *  Created on: 6 Aug 2019
 *      Author: Yarden
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#ifndef STACK_H_
#define STACK_H_



#endif /* STACK_H_ */

typedef struct Stack {
    List *list;
    ListNode *top;
}Stack;

struct Stack* createStack();

int isEmpty(struct Stack *stack);

void push(struct Stack *stack, void* data);

void *pop (struct Stack *stack);

void *peek(struct Stack *stack);
