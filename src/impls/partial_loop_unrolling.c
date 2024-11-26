#include "opts.h"

void distance_transformer() {
    int input[N][M];
    int distance[N][M];
    int transformed = 0;
    int k = 1;
    int i = 0;
    int j = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j += 4) {
            input[i][j] = current_y[i][j];
            if (j + 1 < M)
                input[i][j + 1] = current_y[i][j + 1];
            if (j + 2 < M)
                input[i][j + 2] = current_y[i][j + 2];
            if (j + 3 < M)
                input[i][j + 3] = current_y[i][j + 3];
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j += 4) {
            distance[i][j] = (input[i][j] == 0) ? 0 : -1;
            if (j + 1 < M)
                distance[i][j + 1] = (input[i][j + 1] == 0) ? 0 : -1;
            if (j + 2 < M)
                distance[i][j + 2] = (input[i][j + 2] == 0) ? 0 : -1;
            if (j + 3 < M)
                distance[i][j + 3] = (input[i][j + 3] == 0) ? 0 : -1;
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

                if (j + 1 < M && distance[i][j + 1] == k - 1) {
                    if (i > 0 && distance[i - 1][j + 1] == -1) {
                        distance[i - 1][j + 1] = k;
                        transformed = 1;
                    }

                    if (i < N - 1 && distance[i + 1][j + 1] == -1) {
                        distance[i + 1][j + 1] = k;
                        transformed = 1;
                    }

                    if (j + 1 > 0 && distance[i][j] == -1) {
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

        if (!transformed)
            break;

        if (k < 255)
            k++;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j += 4) {
            current_y[i][j] = distance[i][j];
            if (j + 1 < M)
                current_y[i][j + 1] = distance[i][j + 1];
            if (j + 2 < M)
                current_y[i][j + 2] = distance[i][j + 2];
            if (j + 3 < M)
                current_y[i][j + 3] = distance[i][j + 3];
        }
    }
}
