#include <string.h>

#include "opts.h"

__global_reg(1) int i; // r4
__global_reg(2) int j; // r5
__global_reg(3) int k; // r6
__global_reg(4) int b; // r7

#pragma arm section rwdata=".dram"
__align(4) int f[2] = {-1, 0};
#pragma arm section

#pragma arm section zidata=".cache"
__align(4) int buffer1[4][M];
__align(4) int buffer2[4][M];
__align(4) int distance[N][M];
#pragma arm section

__inline void calculate_distance(int b) {
    for (j = 0; j < M; j += 4) {
        buffer2[i + b][j] = f[!buffer1[b][j]];
        if (j + 1 < M) buffer2[i + b][j + 1] = f[!buffer1[b][j + 1]];
        if (j + 2 < M) buffer2[i + b][j + 2] = f[!buffer1[b][j + 2]];
        if (j + 3 < M) buffer2[i + b][j + 3] = f[!buffer1[b][j + 3]];
    }
}

__inline void check_neighbors(int b) {
    for (j = 0; j < M; j += 2) {
        if (buffer2[i + b][j] == k - 1) {
            if (i + b > 0 && buffer2[i + b - 1][j] == -1) buffer2[i + b - 1][j] = k;
            if (i + b < (N - 1) && buffer2[i + b + 1][j] == -1) buffer2[i + b + 1][j] = k;
            if (j > 0 && buffer2[i + b][j - 1] == -1) buffer2[i + b][j - 1] = k;
            if (j < (M - 1) && buffer2[i + b][j + 1] == -1) buffer2[i + b][j + 1] = k;
        }
        if (j + 1 < M) {
            if (buffer2[i + b][j + 1] == k - 1) {
                if (i + b > 0 && buffer2[i + b - 1][j + 1] == -1) buffer2[i + b - 1][j + 1] = k;
                if (i + b < (N - 1) && buffer2[i + b + 1][j + 1] == -1) buffer2[i + b + 1][j + 1] = k;
                if (j > -1 && buffer2[i + b][j] == -1) buffer2[i + b][j] = k;
                if (j < (M - 2) && buffer2[i + b][j + 2] == -1) buffer2[i + b][j + 2] = k;
            }
        }
    }
}

#pragma Otime
void distance_transformer() {
    for (i = 0; i < N; i += 4) {
        memcpy(buffer1, &current_y[i][0], 4 * M * sizeof(int));

        calculate_distance(0);
	calculate_distance(1);
	calculate_distance(2);
	calculate_distance(3);

	for (k = 1; k < 255; ++k) {
	    check_neighbors(0);
	    check_neighbors(1);
	    check_neighbors(2);
	    check_neighbors(3);
        }

	memcpy(distance, &buffer2[i][0], 4 * M * sizeof(int));
    }

    memcpy(current_y, distance, N * M * sizeof(int));
}
