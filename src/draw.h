#ifndef DRAW_H
#define DRAW_H
#include "tigr.h"
#include <stdlib.h>

void draw_line(Tigr* screen, float* zbuffer, int x0, int y0, float z0, int x1, int y1, float z1, TPixel color);
void draw_triangle(Tigr* screen, float* zbuffer, int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, TPixel color);
void draw_filled_triangle(Tigr* screen, float* z_buffer, int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, TPixel color);

#endif
