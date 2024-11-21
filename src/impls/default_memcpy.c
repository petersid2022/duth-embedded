#include <string.h>

#include "opts.h"

void distance_transformer() {
    int input[N][M];
    int distance[N][M];
    int transformed = 0;
    int k = 1;
    int i = 0;
    int j = 0;

    memcpy(input, current_y, N * M * sizeof(int));

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (input[i][j] == 0) {
                distance[i][j] = 0;
            } else {
                distance[i][j] = -1;
            }
        }
    }

    for (;;) {
        transformed = 0;

        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
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
            }
        }

        if (!transformed)
            break;

        if (k < 255)
            k++;
    }

    memcpy(current_y, distance, N * M * sizeof(int));
}
