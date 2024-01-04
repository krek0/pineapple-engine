#ifndef DEBUG_H
#define DEBUG_H
#include "stdlib.h"
#include "stdio.h"
#include "struct.h"

void* my_malloc(size_t size);
void my_free(void* ptr);
void print_debug();
void display_mat(float mat[4][4]);
void display_vertice(Vertice* vertice);

#endif
