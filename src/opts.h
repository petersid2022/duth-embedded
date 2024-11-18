#ifndef OPTS_H__
#define OPTS_H__

#define N 372
#define M 496
#define filename "Images/binary/cherry_496x372_BIN.yuv"
#define output "Images/out/output.yuv"

#pragma arm section zidata = "ram"
extern int current_y[N][M];
extern int current_u[N][M];
extern int current_v[N][M];
#pragma arm section

#endif /* OPTS_H__ */
