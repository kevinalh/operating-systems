/* Implements the simulation event queue.
 * 
 * Framework created by Henry M. Walker on 27 September 2004
 * Revised by Janet Davis, 25 September 2010
 * Revised by Jerod Weinman, 10 August 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "scheduler.h"
#include "eventq.h"

/* Global variable: the head node of the event queue. */
eventq_node_t* eventq;

/* Initializes the event queue. */
void eventq_init() {
  eventq = NULL;
}

/* Returns true if the event queue is empty, false otherwise. */
int eventq_empty() {
  return (eventq == NULL);
}

/* Returns the time of the next event.
 * Preconditions:
 *   eventq_empty() is false
 */
double eventq_next_event_time(void) {
  assert(!eventq_empty());
  return eventq->time;
}

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
                    event_handler_t* handler, job_t* job) {

  eventq_node_t* node; 
  eventq_node_t* temp; 

  /* create event node for insertion into event list */
  node = (eventq_node_t*) malloc(sizeof(eventq_node_t));

  if (NULL == node) /* verify malloc */
  {
    perror("Error allocating event queue node");
    exit(EXIT_FAILURE);
  }
     
  node->time = time;
  node->description = description;
  node->handler = handler;
  node->job = job;

  /* put created job event in event queue */
  /* order events by arrival time */
  if ((eventq == NULL) || (time < eventq->time)) {
    /* insert at front of event list */
    node->next = eventq;
    eventq = node;
  } else {
    temp = eventq;
    while ((temp->next != NULL) && (time > temp->next->time)) {
      temp = temp->next;
    }
    node->next = temp->next;
    temp->next = node;
  }
}

/* Handles the next event.
 * Preconditions:
 *  eventq_empty() is false.
 * Postconditions:
 *   Top-level variable eventq becomes eventq->next.
 *   The dequeued eventq_node_t is freed.
 */
void eventq_next( void ) {
  eventq_node_t* event;

  assert(!eventq_empty());

  /* remove next event from event queue */
  event = eventq;
  eventq = eventq->next;

  /* perform work for current event by applying event handler function*/
  (*event->handler) (event->job);

  /* discard the event now that it has been processed */
  free(event);
}

/* Prints the contents of the event queue. */
void eventq_print( void )  {
    eventq_node_t* eventq_node = eventq;
    printf ("Current event list:\n");
    while (eventq_node != NULL) {
      printf("\t%s", eventq_node->description);
      printf ("\ttime: %8.2f\n", eventq_node->time);
      eventq_node = eventq_node->next;
    }
}
