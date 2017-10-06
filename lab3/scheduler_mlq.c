/* Implements an MLQ scheduler. */

#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

/* The ready queues */
job_queue_t ready[NUM_PRIORITY_LEVELS];

/* Initializes the ready queue.  Call before any other functions. */
void ready_queue_init(void) {
	for(int i = 0; i < NUM_PRIORITY_LEVELS; ++i) {
		ready[i].first = NULL;
		ready[i].last = NULL;
	}
}

/* Returns true or false, according to whether any jobs are waiting
 * in the ready queue.
 */
int ready_queue_empty(void) {
	for(int i = NUM_PRIORITY_LEVELS - 1; i >= 0; --i) {
		if(ready[i].first != NULL) return 0;
	}
	return 1;
}

/* Adds the specified job to the ready queue.
 * 
 * Preconditions:
 *   job != NULL
 * Postconditions:
 *   Creates a new node for the job
 *   job is inserted at the end of the queue
 */
void ready_queue_insert(job_t* job) {
  job_queue_node_t* node 
      = (job_queue_node_t *)malloc(sizeof(job_queue_node_t));

  if (!node) {
    perror("Unable to allocate job node");
    exit(EXIT_FAILURE);
  }

  /* copy event data to new node */
  node->job = job;
  
  /* insert node into ready queue*/
	int p = job->priority - 1;
  node->next = NULL;
  if (ready[p].first == NULL) {
    ready[p].first = node;
    ready[p].last  = node;
  } else {
		ready[p].last->next = node;
		ready[p].last = node;
	}
}

/* Removes and returns the job at the head of the ready queue.
 *
 * Postconditions:
 *   If ready_queue_empty(), returns NULL
 *   Otherwise, returns head job and frees the associated node
 */
job_t* ready_queue_select(void) {
  job_t* job;
  job_queue_node_t* old_node;

  /* if no jobs are ready, return NULL */
  if (ready_queue_empty())
    return NULL;

	/* check top non-empty priority */
  int p = NUM_PRIORITY_LEVELS - 1;
	while(p >= 0) {
		if(ready[p].first != NULL) break;
		p--;
	}

  /* next job is at front of queue */
  job = ready[p].first->job;

  /* record node at front of queue */
  old_node = ready[p].first;
  ready[p].first = ready[p].first->next;

  /* check if queue is -now- empty */
  if (ready[p].first == NULL) {
    ready[p].last = NULL; /* make last pointer consistent */
  }

  /* return old front of queue to memory pool */
  free(old_node);

  return job;
}
