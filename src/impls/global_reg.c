#include <string.h>

#include "opts.h"

__global_reg(1) int i; /* r4 */
__global_reg(2) int j; /* r5 */

#pragma Otime
void distance_transformer() {
    __align(8) int input[N][M];
    __align(8) int distance[N][M];
    __align(8) int k = 1;
    __align(8) int temp = 0;
    __align(8) int transformed = 0;

    i = 0;
    j = 0;

    memcpy(input, current_y, N * M * sizeof(int));

    for (i = 0; i < N; i += 4) {
        for (j = 0; j < M; j += 4) {
            temp = (input[i][j] == 0);
            distance[i][j] = temp ? 0 : -1;

            temp = (input[i][j + 1] == 0);
            if (j + 1 < M)
                distance[i][j + 1] = temp ? 0 : -1;

            temp = (input[i][j + 2] == 0);
            if (j + 2 < M)
                distance[i][j + 2] = temp ? 0 : -1;

            temp = (input[i][j + 3] == 0);
            if (j + 3 < M)
                distance[i][j + 3] = temp ? 0 : -1;
        }
        if (i + 1 < N) {
            for (j = 0; j < M; j += 4) {
                temp = (input[i + 1][j] == 0);
                distance[i + 1][j] = temp ? 0 : -1;

                temp = (input[i + 1][j + 1] == 0);
                if (j + 1 < M)
                    distance[i + 1][j + 1] = temp ? 0 : -1;

                temp = (input[i + 1][j + 2] == 0);
                if (j + 2 < M)
                    distance[i + 1][j + 2] = temp ? 0 : -1;

                temp = (input[i + 1][j + 3] == 0);
                if (j + 3 < M)
                    distance[i + 1][j + 3] = temp ? 0 : -1;
            }
        }
        if (i + 2 < N) {
            for (j = 0; j < M; j += 4) {
                temp = (input[i + 2][j] == 0);
                distance[i + 2][j] = temp ? 0 : -1;

                temp = (input[i + 2][j + 1] == 0);
                if (j + 1 < M)
                    distance[i + 2][j + 1] = temp ? 0 : -1;

                temp = (input[i + 2][j + 2] == 0);
                if (j + 2 < M)
                    distance[i + 2][j + 2] = temp ? 0 : -1;

                temp = (input[i + 2][j + 3] == 0);
                if (j + 3 < M)
                    distance[i + 2][j + 3] = temp ? 0 : -1;
            }
        }
        if (i + 3 < N) {
            for (j = 0; j < M; j += 4) {
                temp = (input[i + 3][j] == 0);
                distance[i + 3][j] = temp ? 0 : -1;

                temp = (input[i + 3][j + 1] == 0);
                if (j + 1 < M)
                    distance[i + 3][j + 1] = temp ? 0 : -1;

                temp = (input[i + 3][j + 2] == 0);
                if (j + 2 < M)
                    distance[i + 3][j + 2] = temp ? 0 : -1;

                temp = (input[i + 3][j + 3] == 0);
                if (j + 3 < M)
                    distance[i + 3][j + 3] = temp ? 0 : -1;
            }
        }
    }

    for (;;) {
        transformed = 0;

        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j += 2) {
                if (distance[i][j] == k - 1) {
                    if (i > 0 && distance[i - 1][j] == -1) {
                        distance[i - 1][j] = k;
                        transformed = 1;
                    }

                    if (i < N - 1 && distance[i + 1][j] == -1) {
                        distance[i + 1][j] = k;
                        transformed = 1;
                    }

                    if (j > 0 && distance[i][j - 1] == -1) {
                        distance[i][j - 1] = k;
                        transformed = 1;
                    }

                    if (j < M - 1 && distance[i][j + 1] == -1) {
                        distance[i][j + 1] = k;
                        transformed = 1;
                    }
                }
                if (j + 1 < M) {
                    if (distance[i][j + 1] == k - 1) {
                        if (i > 0 && distance[i - 1][j + 1] == -1) {
                            distance[i - 1][j + 1] = k;
                            transformed = 1;
                        }

                        if (i < N - 1 && distance[i + 1][j + 1] == -1) {
                            distance[i + 1][j + 1] = k;
                            transformed = 1;
                        }

                        if (j > -1 && distance[i][j] == -1) {
                            distance[i][j] = k;
                            transformed = 1;
                        }

                        if (j < M - 2 && distance[i][j + 2] == -1) {
                            distance[i][j + 2] = k;
                            transformed = 1;
                        }
                    }
                }
            }
        }

        if (!transformed)
            break;

        if (k < 255)
            k++;
    }

    memcpy(current_y, distance, N * M * sizeof(int));
}
