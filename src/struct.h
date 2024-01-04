#ifndef STRUCT_H
#define STRUCT_H

#include "tigr.h"

typedef struct
{
    float x, y, z;
} Vertice;

typedef struct
{
    Vertice* v;
    Vertice normal;
} Face;

typedef struct
{
    int n;
    Face* faces;
    TPixel color;
} Obj;

typedef struct
{
    Vertice position ;
    Vertice orientation;
    Vertice normal;
    Vertice up;
} Camera;

#endif
