#include "input.h"

void update_keys(Tigr* screen, Camera* camera)
{
    // Camera go left
    if (tigrKeyHeld(screen, 'A'))
    {
        Vertice new_up;
        new_up.x = camera->up.x * 0.9998476951563 + camera->up.z * 0.0174524064372;
        new_up.z = camera->up.z * 0.9998476951563 - camera->up.x * 0.0174524064372;
        camera->up.x = new_up.x;
        camera->up.z = new_up.z;

        Vertice new_orientation;
        new_orientation.x = camera->orientation.x * 0.9998476951563 + camera->orientation.z * 0.0174524064372;
        new_orientation.z = camera->orientation.z * 0.9998476951563 - camera->orientation.x * 0.0174524064372;
        camera->orientation.x = new_orientation.x;
        camera->orientation.z = new_orientation.z;

        Vertice new_normal;
        new_normal.x = camera->normal.x * 0.9998476951563 + camera->normal.z * 0.0174524064372;
        new_normal.z = camera->normal.z * 0.9998476951563 - camera->normal.x * 0.0174524064372;
        camera->normal.x = new_normal.x;
        camera->normal.z = new_normal.z;
    }
    // Camera go right
    if (tigrKeyHeld(screen, 'E'))
    {
        Vertice new_up;
        new_up.x = camera->up.x * 0.9998476951563 - camera->up.z * 0.0174524064372;
        new_up.z = camera->up.z * 0.9998476951563 + camera->up.x * 0.0174524064372;
        camera->up.x = new_up.x;
        camera->up.z = new_up.z;

        Vertice new_orientation;
        new_orientation.x = camera->orientation.x * 0.9998476951563 - camera->orientation.z * 0.0174524064372;
        new_orientation.z = camera->orientation.z * 0.9998476951563 + camera->orientation.x * 0.0174524064372;
        camera->orientation.x = new_orientation.x;
        camera->orientation.z = new_orientation.z;

        Vertice new_normal;
        new_normal.x = camera->normal.x * 0.9998476951563 - camera->normal.z * 0.0174524064372;
        new_normal.z = camera->normal.z * 0.9998476951563 + camera->normal.x * 0.0174524064372;
        camera->normal.x = new_normal.x;
        camera->normal.z = new_normal.z;
    }
    // Camera go up
    if (tigrKeyHeld(screen, 'R'))
    {
        Vertice new_normal;
        new_normal.z = camera->normal.z * 0.9998476951563 - camera->normal.y * 0.0174524064372;
        new_normal.y = camera->normal.y * 0.9998476951563 + camera->normal.z * 0.0174524064372;
        camera->normal.y = new_normal.y;
        camera->normal.z = new_normal.z;

        Vertice new_up, new_orientation;
        new_up.z = camera->up.z * 0.9998476951563 - camera->up.y * 0.0174524064372;
        new_up.y = camera->up.y * 0.9998476951563 + camera->up.z * 0.0174524064372;
        camera->up.y = new_up.y;
        camera->up.z = new_up.z;

        new_orientation.z = camera->orientation.z * 0.9998476951563 - camera->orientation.y * 0.0174524064372;
        new_orientation.y = camera->orientation.y * 0.9998476951563 + camera->orientation.z * 0.0174524064372;
        camera->orientation.y = new_orientation.y;
        camera->orientation.z = new_orientation.z;
    }
    // Camera go down
    if (tigrKeyHeld(screen, 'F'))
    {
        Vertice new_normal;
        new_normal.z = camera->normal.z * 0.9998476951563 + camera->normal.y * 0.0174524064372;
        new_normal.y = camera->normal.y * 0.9998476951563 - camera->normal.z * 0.0174524064372;
        camera->normal.y = new_normal.y;
        camera->normal.z = new_normal.z;

        Vertice new_up, new_orientation;
        new_up.z = camera->up.z * 0.9998476951563 + camera->up.y * 0.0174524064372;
        new_up.y = camera->up.y * 0.9998476951563 - camera->up.z * 0.0174524064372;
        camera->up.y = new_up.y;
        camera->up.z = new_up.z;

        new_orientation.z = camera->orientation.z * 0.9998476951563 + camera->orientation.y * 0.0174524064372;
        new_orientation.y = camera->orientation.y * 0.9998476951563 - camera->orientation.z * 0.0174524064372;
        camera->orientation.y = new_orientation.y;
        camera->orientation.z = new_orientation.z;
    }
    // Left
    if (tigrKeyHeld(screen, 'Q'))
    {
        camera->position.x -= camera->normal.x;
        camera->position.y -= camera->normal.y;
        camera->position.z -= camera->normal.z;
    }
    // Right
    if (tigrKeyHeld(screen, 'D'))
    {
        camera->position.x += camera->normal.x;
        camera->position.y += camera->normal.y;
        camera->position.z += camera->normal.z;
    }
    // Forward
    if (tigrKeyHeld(screen, 'Z'))
    {
        camera->position.x -= camera->orientation.x;
        camera->position.y -= camera->orientation.y;
        camera->position.z -= camera->orientation.z;
    }
    // Backward
    if (tigrKeyHeld(screen, 'S'))
    {
        camera->position.x += camera->orientation.x;
        camera->position.y += camera->orientation.y;
        camera->position.z += camera->orientation.z;
    }
    // UP
    if (tigrKeyHeld(screen, TK_SPACE))
    {
        camera->position.x -= camera->up.x;
        camera->position.y -= camera->up.y;
        camera->position.z -= camera->up.z;
    }
    // DOWN
    if (tigrKeyHeld(screen, TK_SHIFT))
    {
        camera->position.x += camera->up.x;
        camera->position.y += camera->up.y;
        camera->position.z += camera->up.z;
    }
}
