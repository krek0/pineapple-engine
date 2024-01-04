#ifndef RENDER_H
#define RENDER_H
#include "obj.h"
#include "tigr.h"
#include <math.h>
#include "calcul.h"
#include "draw.h"
#include "debug.h"

void render_obj(Tigr* screen, float* depth_buffer, Obj* obj, Camera* camera);

#endif
