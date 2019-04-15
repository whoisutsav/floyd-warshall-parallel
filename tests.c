#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "command_line_interface.h"
#include "graph_processor.h"

int** malloc_2d_matrix(int n) {
  int ** m = malloc(n * sizeof(int*));
  for(int i=0; i<n; i++) {
    m[i] = malloc(n * sizeof(int));
  }

  return m;
}

void test_fw_parallel_fully_connected() {
  int n = 1000;
  int ** m = malloc_2d_matrix(n);
  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) m[i][j] = 0;
      else m[i][j] = 1;
    }
  }

  fw_parallel(m, n, 200);

  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) assert(m[i][j] == 0);
      else assert(m[i][j] == 1);
    }
  }
}

void test_fw_parallel_serial_fully_connected_constant() {
  int n = 500;
  int ** m = malloc_2d_matrix(n);
  int ** s = malloc_2d_matrix(n); 
  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) { m[i][j] = 0; s[i][j] = 0; }
      else { m[i][j] = 1; s[i][j] = 1; }
    }
  }

  fw_parallel(m, n, 10);
  fw_serial(s, n);

  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) { assert(m[i][j] == 0); assert(m[i][j] == s[i][j]); }
      else { assert(m[i][j] == 1); assert(m[i][j] == s[i][j]); }
    }
  }
}

void test_fw_parallel_serial_fully_connected() {
  int n = 500;
  int ** m = malloc_2d_matrix(n);
  int ** s = malloc_2d_matrix(n); 
  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) { m[i][j] = 0; s[i][j] = 0; }
      else { m[i][j] = (i+j); s[i][j] = (i+j); }
    }
  }

  fw_parallel(m, n, 10);
  fw_serial(s, n);

  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j) { assert(m[i][j] == 0); assert(m[i][j] == s[i][j]); }
      else { assert(m[i][j] == s[i][j]); }
    }
  }
}

void test_fw_parallel_star_singly_directed() {
  int n = 100;
  int ** m = malloc_2d_matrix(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if(i == j) m[i][j] = 0;
      else if (j == 0) m[i][j] = 10;
      else m[i][j] = 10000000;
    }
  }

  fw_parallel(m, n, 10);

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if(i == j) assert(m[i][j] == 0);
      else if (j == 0) assert(m[i][j] == 10);
      else assert(m[i][j] == 10000000);
    }
  }
}

void test_fw_parallel_star_doubly_directed() {
  int n = 100;
  int ** m = malloc_2d_matrix(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if(i == j) m[i][j] = 0;
      else if (i==0 || j == 0) m[i][j] = 10;
      else m[i][j] = 10000000;
    }
  }

  fw_parallel(m, n, 10);

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if(i == j) assert(m[i][j] == 0);
      else if (i==0 || j == 0) assert(m[i][j] == 10);
      else assert(m[i][j] == 20);
    }
  }
}

void test_read_bad_file() {
  int *** m = malloc(sizeof(int **));

  printf("Bad file error message test:\n");
  int r = read_adj_matrix(m, "test_files/empty.txt");
  assert(r == -1); 

  printf("Bad file error message test:\n");
  int s = read_adj_matrix(m, "does_not_exist.txt");
  assert (s == -1);
}

void test_read_file() {
  int *** m = malloc(sizeof(int **));
  int r = read_adj_matrix(m, "test_files/test2.txt");

  assert(r == 6);


  for (int i=0; i < 6; i++) {
    for (int j=0; j < 6; j++) {
      if (i==j) assert((*m)[i][j] == 0);
      else assert((*m)[i][j] == 1);
    }
  }
}

void assert_matrix_eq_example(int **A) {
  assert(A[0][0] == 0); 
  assert(A[0][1] == -1); 
  assert(A[0][2] == -2); 
  assert(A[0][3] == 0); 
  assert(A[1][0] == 4); 
  assert(A[1][1] == 0); 
  assert(A[1][2] == 2); 
  assert(A[1][3] == 4); 
  assert(A[2][0] == 5); 
  assert(A[2][1] == 1); 
  assert(A[2][2] == 0); 
  assert(A[2][3] == 2); 
  assert(A[3][0] == 3); 
  assert(A[3][1] == -1); 
  assert(A[3][2] == 1); 
  assert(A[3][3] == 0); 
}

void test_end_to_end() {
  int *** m = malloc(sizeof(int **));
  int *** k = malloc(sizeof(int **));
  int *** o = malloc(sizeof(int **));

  int n = read_adj_matrix(m, "test_files/test.txt");
  int r = read_adj_matrix(k, "test_files/test.txt");

  fw_serial(*m, n);
  fw_parallel(*k, r, 10);

  assert(r == 4);
  assert(n == 4);
  
  assert_matrix_eq_example(*m);
  assert_matrix_eq_example(*k);

  write_adj_matrix(*m, 4, "test_files/test_output.txt");
  int t = read_adj_matrix(o, "test_files/test_output.txt");
  assert(t == 4);
  assert_matrix_eq_example(*o);
}

int main(int argc, char* argv[]) {
  test_fw_parallel_fully_connected();
  test_fw_parallel_serial_fully_connected_constant(); 
  test_fw_parallel_serial_fully_connected(); 
  test_fw_parallel_star_singly_directed();
  test_fw_parallel_star_doubly_directed();
  test_read_bad_file();
  test_read_file();
  test_end_to_end(); 
  printf("All tests passed.\n");
}
