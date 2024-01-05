#include "render.h"

// Array is a array of a triangle = 3 vertice + one normal vertice
void _append_triangle(Vertice** array, Vertice v[3], Vertice* normal, int* len, int* capacity)
{
    if (*len == *capacity) // Need to realoc space
    {
        *capacity = *capacity * 2;
        *array = realloc(*array, sizeof(Vertice) * (*capacity) * 4);
        /*
        Vertice* new_array = my_malloc(sizeof(Vertice) * *capacity * 4);
        for (int i = 0; i < *len*4; i++)
            new_array[i] = (*array)[i];
        my_free(*array);
        *array = new_array;
        */
    }
    int index = (*len) * 4;
    (*array)[index] = v[0];
    (*array)[index+1] = v[1];
    (*array)[index+2] = v[2];
    (*array)[index+3] = *normal;
    *len = *len + 1;
}

void copy_vertice(Vertice* dst_vertice, Vertice* src_vertice)
{
    dst_vertice->x = src_vertice->x;
    dst_vertice->y = src_vertice->y;
    dst_vertice->z = src_vertice->z;
}

// side
// If clipp return the number of new triangle (0,1,2)
// Return -1 if the triangle in on screen
// left: l, right: r, top: t, bottom: b, back_screen (z < 0): s
int clip_triangle(Vertice triangle[3], Vertice out_triangle1[3], Vertice out_triangle2[3], char side, int value)
{
    float test_value;
    char out_n = 0;
    char out_points[3];
    char in_points[3];
    float screen_z = 0.1;
    // Count and stock point out and in
    for (int i = 0; i < 3; i++)
    {
        switch (side)
        {
            case 'l':
            case 'r': test_value = triangle[i].x; break;
            case 't':
            case 'b': test_value = triangle[i].y; break;
            case 's': test_value = triangle[i].z-screen_z; break;
        }
        if ((value == 0 && test_value < 0) || (value != 0 && test_value > value))
        {
            out_points[out_n] = i;
            out_n += 1;
        }
        else
        {
            in_points[i-out_n] = i;
        }
    }
    // Different case dependant of number of points outside
    if (out_n == 0) // no point outisde keep the original triangle
    {
        return -1;
    }
    else if (out_n == 1) // 1 point outside need two new triangles
    {
        float pente_0, pente_bis_0, pente_1, pente_bis_1;
        Vertice new_points[2];
        switch (side)
        {
            case 't':
            case 'b':
                // delta x / delta y
                pente_0 = (triangle[out_points[0]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[0]].y - triangle[in_points[0]].y);
                // delta z / delta y
                pente_bis_0 = (triangle[out_points[0]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[0]].y - triangle[in_points[0]].y);

                // delta x / delta y
                pente_1 = (triangle[out_points[0]].x - triangle[in_points[1]].x) /
                               (triangle[out_points[0]].y - triangle[in_points[1]].y);
                // delta z / delta y
                pente_bis_1 = (triangle[out_points[0]].z - triangle[in_points[1]].z) /
                               (triangle[out_points[0]].y - triangle[in_points[1]].y);
                new_points[0].x = pente_0*(value-triangle[out_points[0]].y) + triangle[out_points[0]].x;
                new_points[0].y = value;
                new_points[0].z = pente_bis_0*(value-triangle[out_points[0]].y) + triangle[out_points[0]].z;
            
                new_points[1].x = pente_1*(value-triangle[out_points[0]].y) + triangle[out_points[0]].x;
                new_points[1].y = value;
                new_points[1].z = pente_bis_1*(value-triangle[out_points[0]].y) + triangle[out_points[0]].z;
                break;
            case 'l':
            case 'r':
                // delta y / delta x
                pente_0 = (triangle[out_points[0]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[0]].x - triangle[in_points[0]].x);
                // delta z / delta x
                pente_bis_0 = (triangle[out_points[0]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[0]].x - triangle[in_points[0]].x);

                // delta y / delta x
                pente_1 = (triangle[out_points[0]].y - triangle[in_points[1]].y) /
                               (triangle[out_points[0]].x - triangle[in_points[1]].x);
                // delta z / delta x
                pente_bis_1 = (triangle[out_points[0]].z - triangle[in_points[1]].z) /
                               (triangle[out_points[0]].x - triangle[in_points[1]].x);
      
                new_points[0].x = value;
                new_points[0].y = pente_0*(value-triangle[out_points[0]].x) + triangle[out_points[0]].y;
                new_points[0].z = pente_bis_0*(value-triangle[out_points[0]].x) + triangle[out_points[0]].z;
            
                new_points[1].x = value;
                new_points[1].y = pente_1*(value-triangle[out_points[0]].x) + triangle[out_points[0]].y;
                new_points[1].z = pente_bis_1*(value-triangle[out_points[0]].x) + triangle[out_points[0]].z;
                break;
            case 's':
                // delta x / delta z
                pente_0 = (triangle[out_points[0]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[0]].z - triangle[in_points[0]].z);
                // delta y / delta z
                pente_bis_0 = (triangle[out_points[0]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[0]].z - triangle[in_points[0]].z);

                // delta x / delta z
                pente_1 = (triangle[out_points[0]].x - triangle[in_points[1]].x) /
                               (triangle[out_points[0]].z - triangle[in_points[1]].z);
                // delta y / delta z
                pente_bis_1 = (triangle[out_points[0]].y - triangle[in_points[1]].y) /
                               (triangle[out_points[0]].z - triangle[in_points[1]].z);

                new_points[0].x = pente_0 * (screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].x;
                new_points[0].y = pente_bis_0 * (screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].y;
                new_points[0].z = value;

                new_points[1].x = pente_1 * (screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].x;
                new_points[1].y = pente_bis_1 * (screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].y;
                new_points[1].z = value;
            break;
        }
        copy_vertice(&out_triangle1[0], &new_points[0]);
        copy_vertice(&out_triangle1[1], &triangle[in_points[0]]);
        copy_vertice(&out_triangle1[2], &triangle[in_points[1]]);

        copy_vertice(&out_triangle2[0], &new_points[0]);
        copy_vertice(&out_triangle2[1], &triangle[in_points[1]]);
        copy_vertice(&out_triangle2[2], &new_points[1]);
        return 2; 
    }
    else if (out_n == 2) // 2 point outside need one new triangle0
    {
        float pente_0, pente_bis_0, pente_1, pente_bis_1;
        Vertice new_points[2];
        switch (side)
        {
            case 't':
            case 'b':
                pente_0 = (triangle[out_points[0]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[0]].y - triangle[in_points[0]].y);
                pente_bis_0 = (triangle[out_points[0]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[0]].y - triangle[in_points[0]].y);

                pente_1 = (triangle[out_points[1]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[1]].y - triangle[in_points[0]].y);
                pente_bis_1 = (triangle[out_points[1]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[1]].y - triangle[in_points[0]].y);
                new_points[0].x = pente_0*(value-triangle[out_points[0]].y) + triangle[out_points[0]].x;
                new_points[0].y = value;
                new_points[0].z = pente_bis_0*(value-triangle[out_points[0]].y) + triangle[out_points[0]].z;
            
                new_points[1].x = pente_1*(value-triangle[out_points[1]].y) + triangle[out_points[1]].x;
                new_points[1].y = value;
                new_points[1].z = pente_bis_1*(value-triangle[out_points[1]].y) + triangle[out_points[1]].z;
                break;
            case 'l':
            case 'r':
                pente_0 = (triangle[out_points[0]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[0]].x - triangle[in_points[0]].x);  
                pente_bis_0 = (triangle[out_points[0]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[0]].x - triangle[in_points[0]].x);


                pente_1 = (triangle[out_points[1]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[1]].x - triangle[in_points[0]].x);
                pente_bis_1 = (triangle[out_points[1]].z - triangle[in_points[0]].z) /
                               (triangle[out_points[1]].x - triangle[in_points[0]].x);
            
                new_points[0].x = value;
                new_points[0].y = pente_0*(value-triangle[out_points[0]].x) + triangle[out_points[0]].y;
                new_points[0].z = pente_bis_0*(value-triangle[out_points[0]].x) + triangle[out_points[0]].z;
            
                new_points[1].x = value;
                new_points[1].y = pente_1*(value-triangle[out_points[1]].x) + triangle[out_points[1]].y;
                new_points[1].z = pente_bis_1*(value-triangle[out_points[1]].x) + triangle[out_points[1]].z;
                break;
            case 's':
                pente_0 = (triangle[out_points[0]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[0]].z - triangle[in_points[0]].z);  
                pente_bis_0 = (triangle[out_points[0]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[0]].z - triangle[in_points[0]].z);


                pente_1 = (triangle[out_points[1]].x - triangle[in_points[0]].x) /
                               (triangle[out_points[1]].z - triangle[in_points[0]].z);
                pente_bis_1 = (triangle[out_points[1]].y - triangle[in_points[0]].y) /
                               (triangle[out_points[1]].z - triangle[in_points[0]].z);
            
                new_points[0].x = pente_0*(screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].x;
                new_points[0].y = pente_bis_0*(screen_z - triangle[out_points[0]].z) + triangle[out_points[0]].y;
                new_points[0].z = screen_z;
                        
                new_points[1].x = pente_1*(screen_z - triangle[out_points[1]].z) + triangle[out_points[1]].x;
                new_points[1].y = pente_bis_1*(screen_z - triangle[out_points[1]].z) + triangle[out_points[1]].y;
                new_points[1].z = screen_z;
            break;
        }
        copy_vertice(&out_triangle1[0], &new_points[0]);
        copy_vertice(&out_triangle1[1], &new_points[1]);
        copy_vertice(&out_triangle1[2], &triangle[in_points[0]]);
        return 1; 
 
    }
    else // 3 point outside no render
        return 0;
}

void _draw_triangle(Tigr* screen, float* depth_buffer, Vertice triangle[3], Vertice* normal, TPixel color)
{
    Vertice light = {0,-0.9,0.4358898944};
    float light_percentage = dot_product(&light, normal);
    light_percentage = -light_percentage;
    if (light_percentage < 0) light_percentage = 0;
    light_percentage = 0.6 * light_percentage + 0.4;
    color.r = color.r * light_percentage;
    color.g = color.g * light_percentage;
    color.b = color.b * light_percentage;
    draw_filled_triangle(screen, depth_buffer,
                         triangle[0].x, triangle[0].y, triangle[0].z,
                         triangle[1].x, triangle[1].y, triangle[1].z,
                         triangle[2].x, triangle[2].y, triangle[2].z,
                         color);
}

void render_obj(Tigr* screen, float* depth_buffer, Obj* obj, Camera* camera)
{
    // Projection matrix
    float zNear = 1;
    float zFar = 100;
    float fov = 80;
    float screenRatio = (float)screen->w / (float)screen->h;
    float rad = 1.0 / tanf( fov / 2 * TO_RADIANS); // 1 / tan(fov/2)
    
    float projection_mat[4][4] = {0};
    projection_mat[0][0] = rad;
    projection_mat[1][1] = rad * screenRatio;
    projection_mat[2][2] = zFar / (zFar - zNear);
    projection_mat[2][3] = (zFar * zNear) / (zNear - zFar);
    projection_mat[3][2] = 1.0;

    // Camera matrix
    float camera_mat[4][4] = {0};
    camera_mat[3][3] = 1;
    camera_mat[0][0] = camera->normal.x;
    camera_mat[0][1] = camera->normal.y;
    camera_mat[0][2] = camera->normal.z;
    camera_mat[0][3] = dot_product(&camera->position, &camera->normal);

    camera_mat[1][0] = camera->up.x;
    camera_mat[1][1] = camera->up.y;
    camera_mat[1][2] = camera->up.z;
    camera_mat[1][3] = dot_product(&camera->position, &camera->up);

    camera_mat[2][0] = camera->orientation.x;
    camera_mat[2][1] = camera->orientation.y;
    camera_mat[2][2] = camera->orientation.z;
    camera_mat[2][3] = dot_product(&camera->position, &camera->orientation);

    // Camera + projection
    float final_mat[4][4];
    matrix_4x4_multiplication(projection_mat, camera_mat, final_mat);
    int capacity = obj->n; // Start with a capacity of n to do less resize
    int len = 0;
    Vertice* triangle_array = my_malloc(sizeof(Vertice)*4*capacity);
    
    Vertice* tmp_triangle_array;
    int tmp_capacity;
    int tmp_len;

    // Loop each faces
    for (int i = 0; i < obj->n; i++)
    {
        Vertice camera_to_obj;
        Vertice fake_position;
        // Check angle between normal vector and camera to obj vector
        sub_vertice(&camera->orientation, &camera->position, &fake_position);
        sub_vertice(&obj->faces[i].v[2], &fake_position, &camera_to_obj);
        TPixel color = {255, 0, 255, 255};

        if (dot_product(&camera_to_obj, &obj->faces[i].normal) < 0)
        {
            Vertice transformed_points[3];
            // Loop on each vertice of face
            for (int j = 0; j < 3; j++)
            {
                // Projection + camera
                matrix_transformation(&obj->faces[i].v[j], &transformed_points[j], final_mat);
                // Scaling
                transformed_points[j].x *= -1;
                transformed_points[j].y *= -1;
                transformed_points[j].x += 1;
                transformed_points[j].y += 1;
                transformed_points[j].x *= 0.5 * screen->w;
                transformed_points[j].y *= 0.5 * screen->h;
            }
            _append_triangle(&triangle_array, transformed_points, &obj->faces[i].normal, &len, &capacity);
         }
    }
    // Clip
    const char sides[] = {'l', 'r', 't', 'b', 's'};
    const int values[] = {0, screen->w, 0, screen->h, 0};
    Vertice out_triangle1[3];
    Vertice out_triangle2[3];
    for (int k = 0; k < 5; k++) // clip the five plans
    {
        tmp_len = 0;
        tmp_capacity = len; // start with len capacity to do less resize
        Vertice* tmp_triangle_array = my_malloc(sizeof(Vertice)*4*tmp_capacity); // Alloc tmp array
        for (int j = 0; j < len; j++)
        {
            int n = clip_triangle(&triangle_array[j*4], out_triangle1, out_triangle2, sides[k], values[k]);
            if (n == -1) // no clipping
                _append_triangle(&tmp_triangle_array, &triangle_array[j*4], &triangle_array[j*4+3], &tmp_len, &tmp_capacity);
            else
            {
                if (n == 1 || n == 2)
                    _append_triangle(&tmp_triangle_array, out_triangle1, &triangle_array[j*4+3], &tmp_len, &tmp_capacity);
                if (n == 2)
                    _append_triangle(&tmp_triangle_array, out_triangle2, &triangle_array[j*4+3], &tmp_len, &tmp_capacity);
            }
        }
        my_free(triangle_array);
        triangle_array = tmp_triangle_array;
        len = tmp_len;
        capacity = tmp_capacity;
    }
    for (int i = 0; i < len; i++) // finaly draw clipped triangles
    {
        _draw_triangle(screen, depth_buffer, &triangle_array[i*4], &triangle_array[i*4+3], obj->color);
    }
    my_free(triangle_array);
}
