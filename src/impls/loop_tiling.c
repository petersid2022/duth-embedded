#include "opts.h"

void distance_transformer() {
    int input[N][M];
    int distance[N][M];
    int transformed = 0;
    int k = 1;
    int i = 0;
    int j = 0;
    int ii = 0;
    int jj = 0;
    int tileSize = 32;

    for (i = 0; i < N; i += tileSize) {
        for (j = 0; j < M; j += tileSize) {
            for (ii = i; ii < i + tileSize && ii < N; ++ii) {
                for (jj = j; jj < j + tileSize && jj < M; ++jj) {
                    input[ii][jj] = current_y[ii][jj];
                }
            }
        }
    }

    for (i = 0; i < N; i += tileSize) {
        for (j = 0; j < M; j += tileSize) {
            for (ii = i; ii < i + tileSize && ii < N; ++ii) {
                for (jj = j; jj < j + tileSize && jj < M; ++jj) {
                    if (input[ii][jj] == 0) {
                        distance[ii][jj] = 0;
                    } else {
                        distance[ii][jj] = -1;
                    }
                }
            }
        }
    }

    for (;;) {
        transformed = 0;

        for (i = 0; i < N; i += tileSize) {
            for (j = 0; j < M; j += tileSize) {
                for (ii = i; ii < i + tileSize && ii < N; ++ii) {
                    for (jj = j; jj < j + tileSize && jj < M; ++jj) {
                        if (distance[ii][jj] == k - 1) {
                            if (ii > 0 && distance[ii - 1][jj] == -1) {
                                distance[ii - 1][jj] = k;
                                transformed = 1;
                            }

                            if (ii < N - 1 && distance[ii + 1][jj] == -1) {
                                distance[ii + 1][jj] = k;
                                transformed = 1;
                            }

                            if (jj > 0 && distance[ii][jj - 1] == -1) {
                                distance[ii][jj - 1] = k;
                                transformed = 1;
                            }

                            if (jj < M - 1 && distance[ii][jj + 1] == -1) {
                                distance[ii][jj + 1] = k;
                                transformed = 1;
                            }
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

    for (i = 0; i < N; i += tileSize) {
        for (j = 0; j < M; j += tileSize) {
            for (ii = i; ii < i + tileSize && ii < N; ++ii) {
                for (jj = j; jj < j + tileSize && jj < M; ++jj) {
                    current_y[ii][jj] = distance[ii][jj];
                }
            }
        }
    }
}
