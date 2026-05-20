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
    Output* simpleResult = solve(grid, movementPoints, findFirstUnvisitedCell);
    Output* bestResult = solve(grid, movementPoints, findBestStartingCell);

    printf("Starting point is {.row=%ld, .column=%ld} \n", simpleResult->path[0].row, simpleResult->path[0].column);
    printf("Best starting point is {.row=%ld, .column=%ld} \n", bestResult->path[0].row, bestResult->path[0].column);

    destroyGrid(grid);

    return 0;
}