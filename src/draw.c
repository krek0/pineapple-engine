#include "draw.h"

void draw_line(Tigr* screen, float* zbuffer, int x0, int y0, float z0, int x1, int y1, float z1, TPixel color)
{
    int sx, sy, dx, dy, err, e2;
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    if (x0 < x1)
        sx = 1;
    else
        sx = -1;

    if (y0 < y1)
        sy = 1;
    else
        sy = -1;

    err = dx - dy;

    do 
    {
        if (y0 < screen->h && y0 >= 0 && x0 < screen->w && x0 >= 0 && z0 > 0)
        {
            int index = y0 * screen->w + x0;
            // Check if the current pixel is in front of the existing pixel in the z-buffer
            if (z0 < zbuffer[index])
            {
                // Update the z-buffer and draw the pixel
                zbuffer[y0 * screen->w + x0] = z0;
                screen->pix[y0 * screen->w + x0] = color;
            }
        }
        else
            break;

        e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
        
        // Interpolate the depth value for the current pixel along the line
        float t = (float)(x0 - x1) / (float)(x0 - x1);
        z0 = z0 + t * (z1 - z0);
    } while (x0 != x1 || y0 != y1);
}

void _draw_horizontal_line(Tigr* screen, float* z_buffer, int xStart, int xEnd, int y, float zStart, float zEnd, TPixel color)
{
    float z = zStart;
    float z_step = (zEnd - zStart) / (xEnd - xStart);
    for (int x = xStart; x <= xEnd; x++)
    {
        if (y < screen->h && y >= 0 && x < screen->w && x >= 0)
        {
            int index = y * screen->w + x;
            if (z < z_buffer[index])
            {
                screen->pix[index] = color;
                z_buffer[index] = z;
            }
        }
        else
            break;
        z += z_step;
    }
}

void _swap_int(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void _swap_float(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void draw_filled_triangle(Tigr* screen, float* z_buffer, int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, TPixel color)
{
    // Sort the vertices by y-coordinate
    if (y0 > y1) { _swap_int(&x0, &x1); _swap_int(&y0, &y1); _swap_float(&z0, &z1); }
    if (y0 > y2) { _swap_int(&x0, &x2); _swap_int(&y0, &y2); _swap_float(&z0, &z2); }
    if (y1 > y2) { _swap_int(&x1, &x2); _swap_int(&y1, &y2); _swap_float(&z1, &z2); }

    // Calculate the steps of two lines of the triangle
    float xstep1 = (float)(x1 - x0) / (y1 - y0);
    float xstep2 = (float)(x2 - x0) / (y2 - y0);
    float zstep1 = (z1 - z0) / (y1 - y0);
    float zstep2 = (z2 - z0) / (y2 - y0);

    if (y1 == y0)
    {
        xstep1 = 0;
        zstep1 = 0;
    }
    if (y2 == y0)
    {
        xstep2 = 0;
        zstep2 = 0;
    }

    // Draw the upper part of the triangle
    for (int y = y0; y <= y1; y++)
    {
        int xStart = x0 + (int)((y - y0) * xstep1);
        int xEnd = x0 + (int)((y - y0) * xstep2);
        float zStart = z0 + (y - y0) * zstep1;
        float zEnd = z0 + (y - y0) * zstep2;

        if (xStart > xEnd)
        {
            _swap_int(&xStart, &xEnd);
            _swap_float(&zStart, &zEnd);
        }
        if (xStart < 0) xStart = 0;
        if (xStart > screen->w) xStart = screen->w;
        if (xEnd < 0) xEnd = 0;
        if (xEnd > screen->w) xEnd = screen->w;

        _draw_horizontal_line(screen, z_buffer, xStart, xEnd, y, zStart, zEnd, color);
    }

    // Draw the lower part of the triangle
    xstep1 = (float)(x2 - x1) / (y2 - y1);
    zstep1 = (z2 - z1) / (y2 - y1);

    for (int y = y1 + 1; y <= y2; y++)
    {
        int xStart = x1 + (int)((y - y1) * xstep1);
        int xEnd = x0 + (int)((y - y0) * xstep2);
        float zStart = z1 + (y - y1) * zstep1;
        float zEnd = z0 + (y - y0) * zstep2;

        if (xStart > xEnd)
        {
            _swap_int(&xStart, &xEnd);
            _swap_float(&zStart, &zEnd);
        }
        if (xStart < 0) xStart = 0;
        if (xStart > screen->w) xStart = screen->w;
        if (xEnd < 0) xEnd = 0;
        if (xEnd > screen->w) xEnd = screen->w;

        _draw_horizontal_line(screen, z_buffer, xStart, xEnd, y, zStart, zEnd, color);
    }
}


void draw_triangle(Tigr* screen, float* zbuffer, int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, TPixel color)
{
    draw_line(screen, zbuffer, x0, y0, z0, x1, y1, z1, color);
    draw_line(screen, zbuffer, x1, y1, z1, x2, y2, z2, color);
    draw_line(screen, zbuffer, x2, y2, z2, x0, y0, z0, color);
}
