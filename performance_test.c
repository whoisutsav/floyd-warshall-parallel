#include <stdio.h>
#include <stdlib.h>
#include "graph_processor.h"
#include "stopwatch.h"


int** generate_matrix(int n) {
  int **m = malloc(n * sizeof(int*));
  for (int k=0; k<n; k++) {
    m[k] = malloc(n * sizeof(int));
  }

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      m[i][j] = i == j ? 0 : (i+j); 
    }
  }

  return m;
}

void serial_overhead_test() {
  int n_values[7] = {16, 32, 64, 128, 256, 512, 1024};
  double time_acc;
  StopWatch_t *stopWatch = malloc(sizeof(StopWatch_t));

  for (int i=0; i<7; i++) {
    time_acc=0;
    for(int j=0; j<3; j++) {
      int ** m = generate_matrix(n_values[i]);
      startTimer(stopWatch);
      fw_serial(m, n_values[i]); 
      stopTimer(stopWatch);
      //printf("Serial overhead test, run %d, n=%d: %g\n", (j+1), n_values[i], getElapsedTime(stopWatch)); 
      time_acc += getElapsedTime(stopWatch); 
    }
    printf("Serial overhead test AVERAGE, n=%d: %g\n", n_values[i], time_acc/3); 
  }
}

void parallel_overhead_test() {
  int n_values[7] = {16, 32, 64, 128, 256, 512, 1024};
  double time_acc;
  StopWatch_t *stopWatch = malloc(sizeof(StopWatch_t));

  for (int i=0; i<7; i++) {
    time_acc=0;
    for(int j=0; j<3; j++) {
      int ** m = generate_matrix(n_values[i]);
      startTimer(stopWatch);
      fw_parallel(m, n_values[i], 1); 
      stopTimer(stopWatch);
      //printf("Parallel overhead test, run %d, n=%d: %g\n", (j+1), n_values[i], getElapsedTime(stopWatch)); 
      time_acc += getElapsedTime(stopWatch); 
    }
    printf("Parallel overhead test AVERAGE, n=%d: %g\n", n_values[i], time_acc/3); 
  }
}

void parallel_speedup_test() {
  int n_values[7] = {16, 32, 64, 128, 256, 512, 1024};
  int t_values[7] = {1, 2, 4, 8, 16, 32, 64};
  double time_acc;
  StopWatch_t *stopWatch = malloc(sizeof(StopWatch_t));

  for (int i=0; i<7; i++) {
    for (int j=0; j<7; j++) {
      time_acc=0;
      for (int k=0; k<3; k++) {
        int ** m = generate_matrix(n_values[i]);
        startTimer(stopWatch);
        fw_parallel(m, n_values[i], t_values[j]); 
        stopTimer(stopWatch);
        //printf("Parallel speedup test, run %d, n=%d, t=%d: %g\n", (k+1), n_values[i], t_values[j], getElapsedTime(stopWatch)); 
        time_acc += getElapsedTime(stopWatch); 
      }
      printf("Parallel speedup test AVERAGE, n=%d, t=%d: %g\n", n_values[i], t_values[j], time_acc/3); 
    }
  }
}


int main(int argc, char* argv[]) {
  //serial_overhead_test();
  //parallel_overhead_test();
  parallel_speedup_test();

  return 0;
}
