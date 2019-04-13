#include <stdlib.h>
#include <stdio.h>

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

void fw_parallel(int **dist, int n, int t) {

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

	fw_serial(dist, 4);

	printf("After:\n");
	print_matrix(dist, 4);

	return 0;
}
