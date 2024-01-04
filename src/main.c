#include "3d.h"
#include "calcul.h"
#include "debug.h"
#include "obj.h"
#include "render.h"
#include "struct.h"
#include "tigr.h"
#include "input.h"
#include <math.h>
#include <stdio.h>
#define WIDTH 700
#define HEIGHT 500

int main(int argc, char *argv[])
{
    float width = WIDTH;
    float heigth = HEIGHT;
    Obj test = load_obj_file("obj/current.obj");
    
    Tigr* screen = tigrWindow(width, heigth, "Hello", 0);
    float* depth_buffer = my_malloc(width*heigth*sizeof(float));
    for (int i = 0; i < width*heigth; i++)
        depth_buffer[i] = 0;
    float worldMat[4][4];

    float angle = 0.1;
    float camera_mat[4][4] = {0};
    float camera_translation[4][4] = {0};
    camera_mat[3][3] = 1;
    camera_translation[0][0] = 1;
    camera_translation[1][1] = 1;
    camera_translation[2][2] = 1;
    camera_translation[3][3] = 1;
    float tmpMat[4][4] = {0};
    float tmpMat2[4][4] = {0};
    float tmpMat3[4][4] = {0};
    Camera camera = {{0,0,100}, {0,0,1}, {1,0,0}, {0,1,0}};
    char fps[30];
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
    {
        update_keys(screen, &camera);
        tigrClear(screen, tigrRGB(30, 30, 30));
        render_obj(screen, depth_buffer, &test, &camera);
        
        angle = angle + 0.04;
        for (int i = 0; i < screen->w*screen->h; i++)
            depth_buffer[i] = 1000;
        float time = tigrTime();
        sprintf(fps, "%i/60", (int)(1./time));
        tigrPrint(screen, tfont, 0, 0, tigrRGB(255, 255, 255), fps);
        tigrUpdate(screen);
    }
    free_obj(&test);
    my_free(depth_buffer);
    print_debug();
    tigrFree(screen);
    return 0;
}
