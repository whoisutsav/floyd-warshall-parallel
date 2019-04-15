#include <stdio.h>
#include <stdlib.h>
#include "file_interface.h"
#include "graph_processor.h"

int main(int argc, char* argv[]) {
  int *** m = malloc(sizeof(int**));
  int n;

  if(argc < 3) {
    printf("Usage: fw_parallel [NUM_THREADS] [INPUT_FILE]\n");
    return -1;
  }

  if ((n = read_adj_matrix(m, argv[2])) < 0)
    return -1;
  

  fw_parallel(*m, n, atoi(argv[1]));
  write_adj_matrix(*m, n, "output.txt");
  return 0;
}


