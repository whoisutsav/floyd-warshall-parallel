#include <stdio.h>
#include <stdlib.h>
#include "command_line_interface.h"

int read_adj_matrix(int *** ptr, char* path) {
  int n;
  int **m;
  FILE * fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("File read error\n");
    return -1;    
  };

  // Get matrix size
  if (fscanf(fp, " %d", &n) != 1) {
    printf("File read error\n");
    return -1;
  }

  // Initialize 2-d array
  m = malloc(n * sizeof(int *)); 
  for(int a=0; a < n; a++) {
    m[a] = malloc(n * sizeof(int));
  }

  // Populate array with values from file
  //int r;
  //int z;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      //z = fscanf(fp, "%d", &r);
      //if (z != -1) printf("%d\n", r);
      if(fscanf(fp, " %d", &(m[i][j])) != 1) {
        printf("File read error\n");
        return -1;        
      }
    }
  }

  fclose(fp);

  *ptr = m;
  return n;
}

int write_adj_matrix(int** m, int n, char* path) {
  FILE * fp;
  if ((fp = fopen(path, "w")) == NULL) 
    return -1;

  if (fprintf(fp, "%d\n", n) < 0)
          return -1;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (fprintf(fp, "%d\t", m[i][j]) < 0)
              return -1;
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
  return 0;
}

void debug_print_matrix(int **m, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("%d\t", m[i][j]); 
		}
		printf("\n");
	}
}

// TODO remove
int** debug_get_matrix() {
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

  return dist;

}


