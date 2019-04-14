#ifndef _FILE_INTERFACE_H
#define _FILE_INTERFACE_H

int read_adj_matrix(int *** ptr, char* path); 

int write_adj_matrix(int** m, int n, char* path); 

void debug_print_matrix(int **m, int n); 

#endif
