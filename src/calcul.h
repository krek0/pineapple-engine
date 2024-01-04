#ifndef CALCUL_H
#define CALCUL_H
#include "struct.h"
#include <assert.h>
#include <math.h>


void matrix_transformation (Vertice* in_point, Vertice* out_point, float matrix[4][4]);
float dot_product(Vertice* v1, Vertice* v2);
void cross_product(Vertice* v1, Vertice* v2, Vertice* out);
void add_vertice(Vertice* v1, Vertice* v2, Vertice* out);
void sub_vertice(Vertice* v1, Vertice* v2, Vertice* out);
void matrix_4x4_multiplication(float mat1[4][4], float mat2[4][4], float result[4][4]);
void get_rot_matrix(float out_mat[4][4], float angle, char axe);
void get_translation_matrix(float out_mat[4][4], Vertice* translation);
void normalize(Vertice* vector);
float point_plane_inside(Vertice* point, Vertice* plane_normal, Vertice* plane_point);

#endif
