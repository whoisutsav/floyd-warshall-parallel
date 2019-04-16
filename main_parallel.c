#include <stdio.h>
#include <stdlib.h>
#include "file_rw.h"
#include "graph_processor.h"

int main(int argc, char* argv[]) {
  int *** m = malloc(sizeof(int**));
  int n,t;

  if(argc < 3) {
    printf("Usage: fw_parallel [NUM_THREADS] [INPUT_FILE]\n");
    return 1;
  }

  if ((n = read_adj_matrix(m, argv[2])) < 0) {
    printf("File read error\n");
    return 1;
  }

  if ((t = atoi(argv[1])) < 1) {
    printf("[NUM_THREADS] must be at least 1\n");
    return 1;
  }
  

  fw_parallel(*m, n, t);
  write_adj_matrix(*m, n, "output.txt");
  return 0;
}


