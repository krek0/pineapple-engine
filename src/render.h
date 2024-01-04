#ifndef RENDER_H
#define RENDER_H
#include "obj.h"
#include "tigr.h"
#include "calcul.h"
#include "draw.h"
#include "debug.h"
#include "struct.h"
#include <math.h>
#define TO_RADIANS 0.0174532925

void render_obj(Tigr* screen, float* depth_buffer, Obj* obj, Camera* camera);

#endif
