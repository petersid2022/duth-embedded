#include <string.h>

#include "opts.h"

#define WINDOW_SIZE 16
#define PADDING 1

__global_reg(1) int i; /* r4 */
__global_reg(2) int j; /* r5 */

#pragma arm section rwdata=".rwdata"
__align(4) static int f[2] = {-1, 0};
__align(4) static int k = 1;
__align(4) static int temp = 0;
#pragma arm section

#pragma arm section zidata=".arrays"
__align(4) static int input[N][M];
__align(4) static int distance[N][M];
#pragma arm section

#pragma arm section zidata=".window_buffer"
__align(4) static int temp_buffer[WINDOW_SIZE + 2*PADDING][WINDOW_SIZE + 2*PADDING];
#pragma arm section

static void process_window(int start_i, int start_j) {
    int local_i, local_j;
    int window_height = WINDOW_SIZE;
    int window_width = WINDOW_SIZE;
    
    if (start_i + WINDOW_SIZE > N) window_height = N - start_i;
    if (start_j + WINDOW_SIZE > M) window_width = M - start_j;
    
    for(local_i = 0; local_i < window_height; local_i++) {
        for(local_j = 0; local_j < window_width; local_j++) {
            temp_buffer[local_i + PADDING][local_j + PADDING] = input[start_i + local_i][start_j + local_j];
        }
    }
    
    for(local_i = 0; local_i < window_height; local_i++) {
        for(local_j = 0; local_j < window_width; local_j += 4) {
            int global_i = start_i + local_i;
            int global_j = start_j + local_j;
            
            temp = !input[global_i][global_j];
            distance[global_i][global_j] = f[temp];
            
            if(local_j + 1 < window_width) {
                temp = !input[global_i][global_j + 1];
                distance[global_i][global_j + 1] = f[temp];
            }
            
            if(local_j + 2 < window_width) {
                temp = !input[global_i][global_j + 2];
                distance[global_i][global_j + 2] = f[temp];
            }
            
            if(local_j + 3 < window_width) {
                temp = !input[global_i][global_j + 3];
                distance[global_i][global_j + 3] = f[temp];
            }
        }
    }
}

#pragma Otime
void distance_transformer() {
    memcpy(input, current_y, N * M * sizeof(int));

    for(i = 0; i < N; i += WINDOW_SIZE) {
        for(j = 0; j < M; j += WINDOW_SIZE) {
            process_window(i, j);
        }
    }

LOOP:
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j += 2) {
            if (distance[i][j] == k - 1) {
                if (i > 0 && distance[i - 1][j] == -1) {
                    distance[i - 1][j] = k;
                }

                if (i < N - 1 && distance[i + 1][j] == -1) {
                    distance[i + 1][j] = k;
                }

                if (j > 0 && distance[i][j - 1] == -1) {
                    distance[i][j - 1] = k;
                }

                if (j < M - 1 && distance[i][j + 1] == -1) {
                    distance[i][j + 1] = k;
                }
            }
            if (j + 1 < M) {
                if (distance[i][j + 1] == k - 1) {
                    if (i > 0 && distance[i - 1][j + 1] == -1) {
                        distance[i - 1][j + 1] = k;
                    }

                    if (i < N - 1 && distance[i + 1][j + 1] == -1) {
                        distance[i + 1][j + 1] = k;
                    }

                    if (j > -1 && distance[i][j] == -1) {
                        distance[i][j] = k;
                    }

                    if (j < M - 2 && distance[i][j + 2] == -1) {
                        distance[i][j + 2] = k;
                    }
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
