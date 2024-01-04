#ifndef OBJ_H
#define OBJ_H
#include "tigr.h"
#include "debug.h"
#include "calcul.h"
#include "struct.h"

void free_obj(Obj* obj);
void calcul_normals(Obj* obj);
Obj copy_obj(Obj* src_obj);

#endif
