/* Defines data types and functions related to job descriptions and the 
 * ready queue.
 * 
 * Framework created by Henry M. Walker on 27 September 2004
 * Revised by Janet Davis, 25 September 2010
 * Revised by Jerod Weinman, 10 August 2012
 */

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#define EXIT_FAILURE 1  /* Error-code indicating when something fails */

/* A job entry */
typedef struct job {
	double arrival_time;  /* time when job entered system */
	double last_execution;/* time when the job last finished execution */
	double cpu_time;      /* overall CPU time required for the job */
	int priority;         /* priority value if priority scheduling used */
	double cpu_time_left; /* CPU time remaining for processing the event */
	int has_started;      /* Initially false; set to true when the job 
												 * has been scheduled for the first time. */
} job_t;

/* Linked list type for ready queue */
typedef struct job_queue_node {
	job_t* job;
	struct job_queue_node* next;
} job_queue_node_t;

typedef struct job_queue {
	job_queue_node_t* first;
	job_queue_node_t* last;
} job_queue_t;

/* Initializes the ready queue. */
void ready_queue_init(void);

/* Returns true or false, according to whether any jobs are waiting
 * in the ready queue.
 */
int ready_queue_empty(void);

/* Adds the specified job to the ready queue. */
void ready_queue_insert(job_t* job);

/* Selects the next job to run from the ready queue, removes the job
 * from the queue, and returns it.
 * Preconditions:
 *   ready_queue_empty() is false.
 */
job_t* ready_queue_select(void);

#endif 
