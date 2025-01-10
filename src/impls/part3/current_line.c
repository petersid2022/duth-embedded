#include <string.h>
#include <stdio.h>
#include "opts.h"

__global_reg(1) int i; // r4
__global_reg(2) int j; // r5
__global_reg(3) int k; // r6
__global_reg(4) int b; // r7
__global_reg(5) int s; // r8
__global_reg(6) int n; // r9
__global_reg(7) int m; // r10

#pragma arm section rwdata=".dram"
__align(8) int f[2] = {-1, 0};
#pragma arm section

#pragma arm section zidata=".L1"
__align(8) int current_line[ROWS][M];
#pragma arm section

#pragma arm section zidata=".L2"
__align(8) int distance[N][M];
__align(8) int buffer[TILE_ROWS][M];
#pragma arm section

__inline int strength_reduction(int x, int y) {
    k = !current_line[x][y];
    return f[k];
}

#pragma O2
#pragma Otime
void distance_transformer() {
    __asm("MOV r6, #1");

    memset(distance, -1, N * M * sizeof(int));
    memset(buffer, 0, TILE_ROWS * M * sizeof(int));
    memset(current_line, 0, ROWS * M * sizeof(int));

    for (i = 0; i < N; i += TILE_ROWS) {
        memcpy(buffer, &current_y[i][0], TILE_ROWS * M * sizeof(int));
        for (b = 0; b < TILE_ROWS; b += ROWS) {
            memcpy(current_line, &buffer[b][0], ROWS * M * sizeof(int));
            for (j = 0; j < M; j += 4) {
                distance[i + b][j] = strength_reduction(b % ROWS, j);
                if (j + 1 < M) distance[i + b][j + 1] = strength_reduction(b % ROWS, j + 1);
                if (j + 2 < M) distance[i + b][j + 2] = strength_reduction(b % ROWS, j + 2);
                if (j + 3 < M) distance[i + b][j + 3] = strength_reduction(b % ROWS, j + 3);
            }
        }
    }

LOOP:
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; j += 2) {
            if (distance[i][j] == k - 1) {
                if (i > 0 && distance[i - 1][j] == -1) distance[i - 1][j] = k;
                if (i < N - 1 && distance[i + 1][j] == -1) distance[i + 1][j] = k;
                if (j > 0 && distance[i][j - 1] == -1) distance[i][j - 1] = k;
                if (j < M - 1 && distance[i][j + 1] == -1) distance[i][j + 1] = k;
            }
            if (j + 1 < M) {
                if (distance[i][j + 1] == k - 1) {
                    if (i > 0 && distance[i - 1][j + 1] == -1) distance[i - 1][j + 1] = k;
                    if (i < N - 1 && distance[i + 1][j + 1] == -1) distance[i + 1][j + 1] = k;
                    if (j > -1 && distance[i][j] == -1) distance[i][j] = k;
                    if (j < M - 2 && distance[i][j + 2] == -1) distance[i][j + 2] = k;
                }
            }
        }
    }

    if (k < 255) {
        k++;
        goto LOOP;
    }

    memcpy(current_y, distance, N * M * sizeof(int));
}
