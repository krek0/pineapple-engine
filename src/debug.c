#include "debug.h"

int nballoc = 0;
int nbfree = 0;

void* my_malloc(size_t size)
{
    nballoc += 1;
    return malloc(size);
}

void my_free(void* ptr)
{
    nbfree += 1;
    free(ptr);
}

void print_debug()
{
    printf("malloc: %i\nfree:  %i\n", nballoc, nbfree);
}

void display_mat(float mat[4][4])
{
    printf("====\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%f ", mat[i][j]);
        printf("\n");
    }
    printf("====\n");
}

void display_vertice(Vertice* vertice)
{
    printf("(%f, %f, %f)\n", vertice->x, vertice->y, vertice->z);
}
