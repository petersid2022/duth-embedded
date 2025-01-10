#include <string.h>
#include <stdio.h>
#include "opts.h"

__global_reg(1) int i; // r4
__global_reg(2) int j; // r5
__global_reg(3) int k; // r6
__global_reg(4) int b; // r7
__global_reg(5) int a; // r8 (buffer counter)
__global_reg(6) int c; // r9 (distance counter)
__global_reg(7) int d; // r10 (block counter)

#pragma arm section rwdata=".dram"
__align(8) int x = 0;
__align(8) int y = 0;
__align(8) int bi = 0;
__align(8) int bj = 0;
__align(8) int global_x = 0;
__align(8) int global_y = 0;
__align(8) int f[2] = {-1, 0};
#pragma arm section

#pragma arm section zidata=".L1"
__align(8) int block[ROWS][ROWS];
#pragma arm section

#pragma arm section zidata=".L2"
__align(8) int distance[N][M];
__align(8) int buffer[TILE_ROWS][M];
#pragma arm section

__inline int strength_reduction(int x, int y) {
    d++;
    k = !block[x][y];
    return f[k];
}

#pragma O2
#pragma Otime
void distance_transformer() {
    __asm("MOV r6, #1");

    memset(distance, -1, N * M * sizeof(int));
    memset(buffer, 0, TILE_ROWS * M * sizeof(int));

    for (i = 0; i < N; i += TILE_ROWS) {
        a += TILE_ROWS * M;
        memcpy(buffer, &current_y[i][0], TILE_ROWS * M * sizeof(int));
        for (b = 0; b < TILE_ROWS; b += ROWS) {
            for (bi = 0; bi < TILE_ROWS; bi += ROWS) {
                for (bj = 0; bj < M; bj += ROWS) {
                    for (x = 0; x < ROWS; x++) {
                        for (y = 0; y < ROWS; y++) {
                            block[x][y] = buffer[b + x][bj + y];
                        }
                    }

                    for (x = 0; x < ROWS; x++) {
                        for (y = 0; y < ROWS; y++) {
                            global_x = i + b + x;
                            global_y = bj + y;
                            if (global_x < N && global_y < M) {
                                c++;
                                d++;
                                distance[global_x][global_y] = strength_reduction(x, y);
                            }
                        }
                    }
                }
            }
        }
    }

LOOP:
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; j += 2) {
            c++;
            if (distance[i][j] == k - 1) {
                if (i > 0) c++;
                if (i > 0 && distance[i - 1][j] == -1) distance[i - 1][j] = k;

                if (i < N - 1) c++;
                if (i < N - 1 && distance[i + 1][j] == -1) distance[i + 1][j] = k;

                if (j > 0) c++;
                if (j > 0 && distance[i][j - 1] == -1) distance[i][j - 1] = k;

                if (j < M - 1) c++;
                if (j < M - 1 && distance[i][j + 1] == -1) distance[i][j + 1] = k;
            }

            if (j + 1 < M) {
                c++;
                if (distance[i][j + 1] == k - 1) {
                    if (i > 0) c++;
                    if (i > 0 && distance[i - 1][j + 1] == -1) distance[i - 1][j + 1] = k;

                    if (i < N - 1) c++;
                    if (i < N - 1 && distance[i + 1][j + 1] == -1) distance[i + 1][j + 1] = k;

                    if (j > -1) c++;
                    if (j > -1 && distance[i][j] == -1) distance[i][j] = k;

                    if (j < M - 2) c++;
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

    printf("Accesses to block: %d\n", d);
    printf("Accesses to distance: %d\n", c);
    printf("Accesses to buffer: %d\n", a);
}
