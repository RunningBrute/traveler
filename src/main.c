#include <stdio.h>

#include "Grid.h"
#include "Point.h"

int main()
{
    const size_t ROWS = 10;
    const size_t COLUMNS = 20;

    Grid* grid = createGrid(ROWS, COLUMNS);

    printf("Hello traveler!\n");

    destroyGrid(grid);

    return 0;
}