#include "calcul.h"
#include <math.h>

void matrix_transformation (Vertice* in_point, Vertice* out_point, float matrix[4][4])
{
    // Base calcul
    out_point->x = in_point->x * matrix[0][0] + in_point->y * matrix[0][1] + in_point->z * matrix[0][2] + matrix[0][3];
    out_point->y = in_point->x * matrix[1][0] + in_point->y * matrix[1][1] + in_point->z * matrix[1][2] + matrix[1][3];
    out_point->z = in_point->x * matrix[2][0] + in_point->y * matrix[2][1] + in_point->z * matrix[2][2] + matrix[2][3];

    float w =      in_point->x * matrix[3][0] + in_point->y * matrix[3][1] + in_point->z * matrix[3][2] + matrix[3][3];
    //transform to the 3x3 equivalent matrix
    if (w < 0) // Avoid behind screen point have a positive z value and avoid behind screen rotation
        w = -w;
    if (w != 1 && w != 0)
    {
        out_point->x = out_point->x / w;
        out_point->y = out_point->y / w;
        out_point->z = out_point->z / w;
    }
}

float dot_product(Vertice* v1, Vertice* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void cross_product(Vertice* v1, Vertice* v2, Vertice* out)
{
    out->x = v1->y * v2->z - v1->z * v2->y;
    out->y = v1->z * v2->x - v1->x * v2->z;
    out->z = v1->x * v2->y - v1->y * v2->x;
}

void add_vertice(Vertice* v1, Vertice* v2, Vertice* out)
{
    out->x = v1->x + v2->x;
    out->y = v1->y + v2->y;
    out->z = v1->z + v2->z;
}

void sub_vertice(Vertice* v1, Vertice* v2, Vertice* out)
{
    out->x = v1->x - v2->x;
    out->y = v1->y - v2->y;
    out->z = v1->z - v2->z;
}

void matrix_4x4_multiplication(float mat1[4][4], float mat2[4][4], float result[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = 0.0;
            for (int k = 0; k < 4; ++k)
                result[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}


void get_rot_matrix(float out_mat[4][4], float angle, char axe)
{
    assert ( axe == 'x' || axe == 'y' || axe == 'z');
    if (axe == 'x')
    {
        out_mat[0][0] = 1;
        out_mat[1][1] = cosf(angle);
        out_mat[1][2] = -sinf(angle);
        out_mat[2][1] = sinf(angle);
        out_mat[2][2] = cosf(angle);
    }
    else if (axe == 'y')
    {
        out_mat[0][0] = cosf(angle);
        out_mat[0][2] = sinf(angle);
        out_mat[1][1] = 1;
        out_mat[2][0] = -sinf(angle);
        out_mat[2][2] = cosf(angle);
    }
    else if (axe == 'z')
    {
        out_mat[0][0] = cosf(angle);
        out_mat[0][1] = -sinf(angle);
        out_mat[1][0] = sinf(angle);
        out_mat[1][1] = cosf(angle);
        out_mat[2][2] = 1;
    }
    out_mat[3][3] = 1;
}

void get_translation_matrix(float out_mat[4][4], Vertice* translation)
{
    out_mat[0][0] = 1;
    out_mat[1][1] = 1;
    out_mat[2][2] = 1;
    out_mat[3][3] = 1;

    out_mat[0][3] = translation->x;
    out_mat[1][3] = translation->y;
    out_mat[2][3] = translation->z;
}

void normalize(Vertice* vector)
{
    float len = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
    float invert_len = 1 / sqrtf(len);
    vector->x *= invert_len;
    vector->y *= invert_len;
    vector->z *= invert_len;
}

// 1 if pt is on the side pointed by the normal vector of the plane, -1 in the other case
float point_plane_inside(Vertice* point, Vertice* plane_normal, Vertice* plane_point)
{
    float result = dot_product(plane_normal, point) - dot_product(plane_normal, plane_point);
    if (result > 0)
        return 1;
    else
        return -1;
}
