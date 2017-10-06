/* Defines data structures and functions for managing simulation
 * statistics.
 *
 * Framework created by Henry M. Walker on 27 September 2004
 * Revised by Janet Davis, 20 September 2010
 * Revised by Jerod Weinman, 10 August 2012
 */

#ifndef __STATS_H__
#define __STATS_H__

/* for storing data about the system performance */
typedef struct performance_data {
  int jobs_started;
  int jobs_completed;
  double total_proc_time;
  double total_wait_time;
  double total_turnaround_time;
} performance_data_t;

/* global variable */
performance_data_t stats;

/* call before using stats variable */
void stats_init(void);

/* prints all statistics */
void stats_print(double time);

#endif 
