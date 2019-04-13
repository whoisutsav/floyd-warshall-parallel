// References: https://computing.llnl.gov/tutorials/pthreads/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void print_matrix(int **m, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("%d\t", m[i][j]); 
		}
		printf("\n");
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

typedef struct _t_data {
	int id;
  int n;
  int start_index;
  int end_index;
  int **dist;
  pthread_barrier_t *barrier;
} t_data;

void* t_process(void *arg) {
  t_data *my_data;
  my_data = (t_data *) arg;

  for(int k=0; k<my_data->n; k++) {
    for(int i = my_data->start_index; i < my_data->end_index; i++) {
        for(int j=0; j < my_data->n; j++) {
		      if(my_data->dist[i][j] > (my_data->dist[i][k] + my_data->dist[k][j]))
		  	     my_data->dist[i][j] = my_data->dist[i][k] + my_data->dist[k][j];	
        }
    }
    pthread_barrier_wait(my_data->barrier);
  }
  return NULL; 
}

void fw_parallel(int **dist, int n, int t) {
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, t);

  pthread_t threads[t];
  t_data thread_args[t];
  int rc;

  for(int i=0; i<t; i++) {
		thread_args[i].id = i;
    thread_args[i].n = n;
    thread_args[i].dist = dist;
    thread_args[i].barrier = &barrier; 
    thread_args[i].start_index = (i*n)/t;
    thread_args[i].end_index = ((i+1)*n)/t;

    rc = pthread_create(&threads[i], NULL, t_process, (void *) &thread_args[i]); 

		if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

	for(int j=0; j<t; j++) {
		pthread_join(threads[j], NULL);
	}
}

int main(int argc, char* argv[]) {
	int **dist = malloc(4 * sizeof(int *));
	for (int i=0; i<4; i++) {
		dist[i] = malloc(4 * sizeof(int));
	}	

	dist[0][0] = 0;
	dist[0][1] = 10000000;
	dist[0][2] = -2;
	dist[0][3] = 10000000;
	dist[1][0] = 4;
	dist[1][1] = 0;
	dist[1][2] = 3;
	dist[1][3] = 10000000;
	dist[2][0] = 10000000;
	dist[2][1] = 10000000;
	dist[2][2] = 0;
	dist[2][3] = 2;
	dist[3][0] = 10000000;
	dist[3][1] = -1;
	dist[3][2] = 10000000;
	dist[3][3] = 0;

	printf("Before:\n");
	print_matrix(dist, 4);

	fw_parallel(dist, 4, 1);

	printf("After:\n");
	print_matrix(dist, 4);

	return 0;
}
