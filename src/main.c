#include <stdio.h>
#include <math.h>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"
#include "Helpers.h"

int main()
{
    const size_t movementPoints = 20;
    const size_t rows = 9;
    const size_t cols = 10;
    const Point blockedSquers[] = {{0,0}, {5,3}, {2,3}, {2,4}, {8,4}, {3,9}, {2,9}};
    const size_t blockedSquesrCount = 7;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);
    printPath(result);

    cleanupSolvedOutput(result);
    destroyGrid(grid);

    return 0;
}