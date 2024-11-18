#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "opts.h"

void read_file_bytes(const char *file_name) {
    assert(strlen(file_name) != 0);

    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: fopen() failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            current_y[i][j] = fgetc(fp);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            current_u[i][j] = fgetc(fp);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            current_v[i][j] = fgetc(fp);
        }
    }

    fclose(fp);
}

void write_file_bytes(const char *file_name) {
    assert(strlen(file_name) != 0);

    FILE *fp = fopen(file_name, "wb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: fopen() failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fputc(current_y[i][j], fp);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fputc(current_u[i][j], fp);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fputc(current_v[i][j], fp);
        }
    }

    fclose(fp);
}
