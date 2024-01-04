#include "obj.h"

void free_obj(Obj* obj)
{
    // Loop on faces
    for (int i = 0; i < obj->n ; i++)
    {
        my_free(obj->faces[i].v);
    }
    my_free(obj->faces);
}

void calcul_normals(Obj* obj)
{
    Vertice line1, line2, normal;
    for (int i = 0; i < obj->n; i++)
    {
        // Calcul cross product to get a normal
        sub_vertice(&obj->faces[i].v[1], &obj->faces[i].v[0], &line1);
        sub_vertice(&obj->faces[i].v[3-1], &obj->faces[i].v[0], &line2);
        cross_product(&line1, &line2, &normal);

        // Noramlise the vector
        float len = sqrtf(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x /= len;
        normal.y /= len;
        normal.z /= len;
        obj->faces[i].normal = normal;
    }
}

Obj copy_obj(Obj* src_obj)
{
    Obj new_obj;
    new_obj.n = src_obj->n;
    new_obj.faces = my_malloc(sizeof(Face)*src_obj->n);
    new_obj.color = src_obj->color;
    for (int i = 0; i < src_obj->n; i++)
    {
        new_obj.faces[i].v = my_malloc(sizeof(Vertice)*3);
        new_obj.faces[i].normal = src_obj->faces[i].normal;
        for (int j = 0; j < 3; j++)
        {
            new_obj.faces[i].v[j] = src_obj->faces[i].v[j];
        }
    }
    return new_obj;
}
