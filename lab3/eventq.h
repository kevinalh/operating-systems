/* Defines data types and functions for managing the simuluation event queue.
 *
 * Framework created by Henry M. Walker on 27 September 2004
 * Revised by Janet Davis, 25 September 2010
 * Revised by Jerod Weinman, 10 August 2012
 */

#ifndef __EVENTQ_H__
#define __EVENTQ_H__

#include "scheduler.h"

/* Type for event handler functions */
typedef void event_handler_t (job_t*);

/* event queue node */
typedef struct eventq_node {
  double time;            /* simulation time at which this event occurs */
  const char* description;      /* a textual description of the handler */
  event_handler_t* handler;      /* the handler function for this event */
  job_t* job;                           /* job this event is related to */
  struct eventq_node* next;       /* link to the next event in the list */
} eventq_node_t;

/* Initializes the event queue. */ 
void eventq_init(void);

/* Returns true if the event queue is empty, false otherwise. */
int  eventq_empty(void);

/* Enqueues a new event, given its time, description,
 * event handler, and the job to act on (may be NULL).
 * Preconditions:
 *   events in eventq are ordered by start time
 * Postconditions:
 *   a new event with the given handler, job, and arrival_time
 *     is inserted in eventq
 *   events in eventq are ordered by start time
 */
void eventq_enqueue(double time, const char* description, 
                    event_handler_t* handler, job_t* job);

/* Handles the next event.
 * Preconditions:
 *   eventq_empty() is false.
 * Postconditions:
 *   eventq_next_event_time() gives the completion time of the next event
 *   Top-level variable eventq becomes eventq->next.
 *   The dequeued event_q_node_t is freed.
 */
void eventq_next(void);

/* Returns the time of the next event.
 * Preconditions:
 *   eventq_empty() is false.
 */
double eventq_next_event_time(void);

/* Prints the contents of the event queue. */
void eventq_print(void);

#endif 
