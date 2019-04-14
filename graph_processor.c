/* Graph Processor 
 * 
 * Calculates shortest paths on graphs using Floyd-Warshall Algorithm
 *
 * References: https://computing.llnl.gov/tutorials/pthreads/
 *
 * Author: Utsav Sethi
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "graph_processor.h"

void* thread_func(void *arg) {
  thread_data *td;
  td = (thread_data *) arg;

  for(int k=0; k<td->n; k++) {
    for(int i = td->start_index; i < td->end_index; i++) {
        for(int j=0; j < td->n; j++) {
		      if(td->dist[i][j] > (td->dist[i][k] + td->dist[k][j]))
		  	     td->dist[i][j] = td->dist[i][k] + td->dist[k][j];	
        }
    }
    pthread_barrier_wait(td->barrier);
  }
  return NULL; 
}

void fw_parallel(int **dist, int n, int t) {
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, t);

  pthread_t threads[t];
  thread_data thread_args[t];
  int rc;

  for(int i=0; i<t; i++) {
		thread_args[i].id = i;
    thread_args[i].n = n;
    thread_args[i].dist = dist;
    thread_args[i].barrier = &barrier; 
    thread_args[i].start_index = (i*n)/t;
    thread_args[i].end_index = ((i+1)*n)/t;

    rc = pthread_create(&threads[i], NULL, thread_func, (void *) &thread_args[i]); 

		if (rc){
      printf("ERROR; pthread_create() returned %d\n", rc);
      exit(-1);
    }
  }

	for(int j=0; j<t; j++) {
		pthread_join(threads[j], NULL);
	}
}

void fw_serial(int **dist,  int n) {
	for(int k=0; k < n; k++) {
		for(int i=0; i < n; i++) {
			for(int j=0; j < n; j++) {
				if(dist[i][j] > (dist[i][k] + dist[k][j]))
				   dist[i][j] = dist[i][k] + dist[k][j];	
			}
		}
	}
}




