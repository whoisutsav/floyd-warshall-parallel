#ifndef _GRAPH_PROCESSOR_H
#define _GRAPH_PROCESSOR_H

#include <pthread.h>

typedef struct {
	int id;
  int n;
  int start_index;
  int end_index;
  int **dist;
  pthread_barrier_t *barrier;
} thread_data;

void fw_serial(int **dist,  int n); 
void fw_parallel(int **dist, int n, int t); 

#endif
