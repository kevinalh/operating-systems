/* Implements functions for managing simulation statistics.
 *
 * Framework created by Henry M. Walker on 27 September 2004
 * Revised by Janet Davis, 24 September 2006
 * Revised by Jerod Weinman, 10 August 2012
 */

#include <stdio.h>
#include "stats.h"

/* initializes performance stats */
void stats_init(void) {
  stats.jobs_started = 0;
  stats.jobs_completed = 0;
  stats.total_proc_time = 0.0;
  stats.total_wait_time = 0.0;
  stats.total_turnaround_time = 0.0;
}

/* print current statistics */
void stats_print( double sim_time ) {
    printf("\tCurrent time:\t\t%8.2f\n", sim_time);
    printf("\tNumber of jobs started:\t%8d\n", stats.jobs_started);
    printf("\tNumber of jobs completed:%7d\n", stats.jobs_completed);
    printf("\tSystem throughput:\t%8.4f jobs per unit time\n", stats.jobs_started/ sim_time); 
    printf("\tTotal proc time:\t%8.2f\n", stats.total_proc_time);
    printf("\tTotal turnaround time:\t%8.2f\n", stats.total_turnaround_time);
    printf("\tTotal wait time:\t%8.2f\n", stats.total_wait_time);
    printf("\tAverage turnaround time:\t%8.2f\n", 
	   stats.total_turnaround_time / stats.jobs_started);
    printf("\tAverage wait time:\t%8.2f\n", 
	    stats.total_wait_time / stats.jobs_started);

}
