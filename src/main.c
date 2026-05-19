#include <stdio.h>

#include "Grid.h"
#include "Point.h"

int main()
{
    const size_t rows = 10;
    const size_t cols = 10;
    const Point blockedSquers[] = {{0, 0}, {1, 1}};
    const size_t blockedSquesrCount = sizeof(blockedSquers) / sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);

    printf("Hello traveler!\n");

    destroyGrid(grid);

    return 0;
}