#include <stdio.h>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"

int main()
{
    const size_t rows = 10;
    const size_t cols = 10;
    const Point blockedSquers[] = {{0, 0}, {1, 1}};
    const size_t blockedSquesrCount = sizeof(blockedSquers) / sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);

    const size_t movementPoints = 3;
    Output* result = solve(grid, movementPoints);

    printf("Starting point is {.row=%ld, .column=%ld} \n", result->path[0].row, result->path[0].column);

    destroyGrid(grid);

    return 0;
}