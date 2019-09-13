/*
 * list.h
 *
 *  Created on: 6 Aug 2019
 *      Author: Yarden
 */

#ifndef LIST_H_
#define LIST_H_




typedef struct node {
  void *data;
  struct node *prev;
  struct node *next;
} ListNode;

/*
 * Generic Linked List Type: gll_t
 */
typedef struct {
  int size;
  ListNode *first;
  ListNode *last;
} List;


/*  create new list */
List *listInit();

/*  get/find functions */
void *listGet(List *, int);

/*  add functions */
int listPushBack(List *, void *);

/*  remove functions */
void *listRemove(List *, int);
void *listRemoveByNode(List *list, ListNode *node);
void *gllPopBack(List *);


/*  destructive functions */
void listDestroy(List *);
int removeAllMovesFromCurr(List *list, ListNode *currNode);


#endif /* LIST_H_ */
