#include <stdio.h>
#include <math.h>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"
#include "Helpers.h"

int main()
{
    const size_t movementPoints = 15;
    const size_t rows = 3;
    const size_t cols = 10;
    const Point blockedSquers[] = {};
    const size_t blockedSquesrCount = 0;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);

    return 0;
}