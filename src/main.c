#include "distance_transformer.h"
#include "file.h"
#include "opts.h"

/* Luminance */
int current_y[N][M];

/* Chrominance (color information) */
int current_u[N][M];
int current_v[N][M];

int main() {

    /* Read image bytes to memory */
    read_file_bytes(filename);

    /* Distance transformation */
    distance_transformer();

    /* Write bytes to file */
    write_file_bytes(output);

    return 0;
}
