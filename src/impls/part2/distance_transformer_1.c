#include <string.h>

#include "opts.h"

__global_reg(1) int i; /* r4 */
__global_reg(2) int j; /* r5 */

#pragma arm section rwdata = ".rwdata"
__align(4) static int f[2] = {-1, 0};
__align(4) static int k = 1;
__align(4) static int temp = 0;
#pragma arm section

#pragma Otime
void distance_transformer() {
    __align(8) int input[N][M];
    __align(8) int distance[N][M];

    memcpy(input, current_y, N * M * sizeof(int));

    for (i = 0; i < N; i += 4) {
        for (j = 0; j < M; j += 4) {
            temp = !(input[i][j]);
            distance[i][j] = f[temp];

            if (j + 1 < M) {
                temp = !(input[i][j + 1]);
                distance[i][j + 1] = f[temp];
            }

            if (j + 2 < M) {
                temp = !(input[i][j + 2]);
                distance[i][j + 2] = f[temp];
            }

            if (j + 3 < M) {
                temp = !(input[i][j + 3]);
                distance[i][j + 3] = f[temp];
            }
        }
        if (i + 1 < N) {
            for (j = 0; j < M; j += 4) {
                temp = !(input[i + 1][j]);
                distance[i + 1][j] = f[temp];

                if (j + 1 < M) {
                    temp = !(input[i + 1][j + 1]);
                    distance[i + 1][j + 1] = f[temp];
                }

                if (j + 2 < M) {
                    temp = !(input[i + 1][j + 2]);
                    distance[i + 1][j + 2] = f[temp];
                }

                if (j + 3 < M) {
                    temp = !(input[i + 1][j + 3]);
                    distance[i + 1][j + 3] = f[temp];
                }
            }
        }
        if (i + 2 < N) {
            for (j = 0; j < M; j += 4) {
                temp = !(input[i + 2][j]);
                distance[i + 2][j] = f[temp];

                if (j + 1 < M) {
                    temp = !(input[i + 2][j + 1]);
                    distance[i + 2][j + 1] = f[temp];
                }

                if (j + 2 < M) {
                    temp = !(input[i + 2][j + 2]);
                    distance[i + 2][j + 2] = f[temp];
                }

                if (j + 3 < M) {
                    temp = !(input[i + 2][j + 3]);
                    distance[i + 2][j + 3] = f[temp];
                }
            }
        }
        if (i + 3 < N) {
            for (j = 0; j < M; j += 4) {
                temp = !(input[i + 3][j]);
                distance[i + 3][j] = f[temp];

                if (j + 1 < M) {
                    temp = !(input[i + 3][j + 1]);
                    distance[i + 3][j + 1] = f[temp];
                }

                if (j + 2 < M) {
                    temp = !(input[i + 3][j + 2]);
                    distance[i + 3][j + 2] = f[temp];
                }

                if (j + 3 < M) {
                    temp = !(input[i + 3][j + 3]);
                    distance[i + 3][j + 3] = f[temp];
                }
            }
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
