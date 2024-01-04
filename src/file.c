#include "file.h"

void _append_vertice(Vertice** array, Vertice v, int* len, int* capacity)
{
  // Need to realoc space
  if (*len == *capacity)
  {
    *capacity = *capacity * 2;
    Vertice* new_array = my_malloc(sizeof(Vertice) * *capacity);
    for (int i = 0; i < *len; i++)
      new_array[i] = (*array)[i];
    my_free(*array);
    *array = new_array;
  }
  (*array)[*len] = v;
  *len = *len + 1;
}

void _append_face(Face** array, Face face, int* len, int* capacity)
{
  // Need to realoc space
  if (*len == *capacity)
  {
    *capacity = *capacity * 2;
    Face* new_array = my_malloc(sizeof(Face) * *capacity);
    for (int i = 0; i < *len; i++)
      new_array[i] = (*array)[i];
    my_free(*array);
    *array = new_array;
  }
  (*array)[*len] = face;
  *len = *len + 1;
}

Obj load_obj_file(char* path)
{
  FILE *file;
  file = fopen(path, "r");
  char line[200];
  Vertice* vertices = my_malloc(sizeof(Vertice));
  int vertices_len = 0;
  int vertices_capacity = 1;

  Face* faces = my_malloc(sizeof(Face));
  int faces_len = 0;
  int faces_capacity = 1;

  
  Vertice* normals = my_malloc(sizeof(Vertice));
  int normals_len = 0;
  int normals_capacity = 1;
  while(fgets(line, 200, file))
  {
    // Get vertices
    if (line[0] == 'v' && line[1] == ' ')
    {
      float x,y,z;
      sscanf(line, " v %f %f %f ", &x, &y, &z);
      Vertice v = {x, y, z};
      _append_vertice(&vertices, v, &vertices_len, &vertices_capacity);
    }
    // get normals
    else if (line[0] == 'v' && line[1] == 'n')
    {
      float x,y,z;
      sscanf(line, " vn %f %f %f ", &x, &y, &z);
      Vertice n = {x, y, z};
      _append_vertice(&normals, n, &normals_len, &normals_capacity);
    }
    // get faces
    else if (line[0] == 'f')
    {
      Face face;
      int v1, v2, v3;
      int n1, n2, n3;
      Vertice* v = my_malloc(sizeof(Vertice)*3);
      int normal_are_calculated = 0;
      // Juste vertices
      if (sscanf(line, " f %i %i %i", &v1, &v2, &v3) == 3)
      {
      }
      // Vertices + normals
      else if (sscanf(line, " f %i//%i %i//%i %i//%i", &v1, &n1, &v2, &n2, &v3, &n3) == 6)
      {
        Vertice normal;
        normal.x = (normals[n1-1].x + normals[n2-1].x + normals[n3-1].x) / 3;
        normal.y = (normals[n1-1].y + normals[n2-1].y + normals[n3-1].y) / 3;
        normal.z = (normals[n1-1].z + normals[n2-1].z + normals[n3-1].z) / 3;
        face.normal = normal;
      }
      v[0] = vertices[v1-1];
      v[1] = vertices[v2-1];
      v[2] = vertices[v3-1];
      face.v = v;
      _append_face(&faces, face, &faces_len, &faces_capacity);
    }
  }
  Obj obj;
  obj.color = tigrRGB(10, 210, 240);
  obj.n = faces_len;
  obj.faces = faces;
  my_free(vertices);

  // Calculs normals
  if (normals_len == 0)
  {
    my_free(normals);
    calcul_normals(&obj);
  }
  
  return obj;
}
