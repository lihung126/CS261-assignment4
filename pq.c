/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Li Hung Chen
 * Email:chenlih@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dynarray.h"
#include "pq.h"

#define PARENT_IDX(i) ((i-1)/2)
#define LEFTCHILD_IDX(i) ((i*2)+1)
#define RIGHTCHILD_IDX(i) ((i*2)+2)
/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* pqarr;
	
};



struct pqelement {
  int priority;
  void* val;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pqc=malloc(sizeof(struct pq));
  assert(pqc);
  pqc->	pqarr= dynarray_create();
  
  return pqc;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
assert(pq);
dynarray_free(pq->pqarr);
free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if (dynarray_size(pq->pqarr)==0) return 1;
  
  else return 0;
}



/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
 
void pq_insert(struct pq* pq, void* value, int priority) {
assert(pq);

  struct pqelement *pqi = malloc(sizeof(struct pqelement));
  pqi->val = value;
  pqi->priority = priority;

  int index = 0;

  dynarray_insert(pq->pqarr, -1, pqi);
  index = dynarray_size(pq->pqarr) - 1;
  int p_index = (index - 1) / 2;

  struct pqelement *parent_e;
  struct pqelement *child_e;
  while (index > 0) {
    parent_e = dynarray_get(pq->pqarr, p_index);
    child_e = dynarray_get(pq->pqarr, index);
    if ((parent_e->priority) > (pqi->priority)) {
      struct element *tmp = dynarray_get(pq->pqarr, index);     // swap
      dynarray_set(pq->pqarr, index, parent_e);
      dynarray_set(pq->pqarr, p_index, tmp);

    } else
      break;
    index = p_index;
    p_index = (index - 1) / 2;
  }
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
assert(pq);
assert(dynarray_size(pq->pqarr)>0);

struct pqelement *ele=dynarray_get(pq->pqarr,0);

	return ele->val;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
 assert(pq);
 assert(dynarray_size(pq->pqarr)>0);
 
 struct pqelement* pqfp=dynarray_get(pq->pqarr,0);

	return pqfp->priority;

}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
 

 
void* pq_remove_first(struct pq* pq) {
assert(pq);
assert(dynarray_size(pq->pqarr)>0);

struct pqelement *eleL=dynarray_get(pq->pqarr,-1);
struct pqelement *eleF=dynarray_get(pq->pqarr,0);

dynarray_set(pq->pqarr,0,eleL);
dynarray_remove(pq->pqarr,-1);

  int index = 0;
  int mIdx = dynarray_size(pq->pqarr) - 1;
  int left_Idx = LEFTCHILD_IDX(index);
  int right_Idx = RIGHTCHILD_IDX(index);

  struct pqelement *left_child;
  struct pqelement *right_child;
  struct pqelement *cur_e;

  while (mIdx > left_Idx || mIdx > right_Idx) {
    cur_e = dynarray_get(pq->pqarr, index);
    left_child = dynarray_get(pq->pqarr, left_Idx);
    right_child = dynarray_get(pq->pqarr, right_Idx);

    if (cur_e->priority > left_child->priority || cur_e->priority > right_child->priority) {
      if (right_child->priority >= left_child->priority) {
   
        struct pqelement *tmp = cur_e;
        dynarray_set(pq->pqarr, index, left_child);
        dynarray_set(pq->pqarr, 2 * index + 1, tmp);
        index = 2 * index + 1;

      } else {

        struct pqelement *tmp = cur_e;
        dynarray_set(pq->pqarr, index, right_child);
        dynarray_set(pq->pqarr, 2 * index + 2, tmp);
        index = 2 * index + 2;
      }
    } else {
      index = mIdx;
    }
    left_Idx = LEFTCHILD_IDX(index);
    right_Idx = RIGHTCHILD_IDX(index);
  }


void *val=eleF->val;
free(eleF);
return val;
}
