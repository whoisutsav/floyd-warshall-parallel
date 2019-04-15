#include <stdio.h>
#include <stdlib.h>
#include "command_line_interface.h"
#include "graph_processor.h"


int main(int argc, char* argv[]) {
  int *** m = malloc(sizeof(int**));
  int n;

  if(argc < 2) {
    printf("Usage: fw_serial [INPUT_FILE]\n");
    return -1;
  }

  if((n = read_adj_matrix(m, argv[1])) < 0)
    return -1;
  
  fw_serial(*m, n);
  write_adj_matrix(*m, n, "output.txt");
  return 0;
}


