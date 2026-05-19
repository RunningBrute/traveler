#ifndef SOLVER_H
#define SOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Grid.h"
#include "Point.h"

typedef struct Output
{
    size_t uniqueSquers;
    Point* path;
} Output;

Point findFirstUnvisitedCell(const Grid* grid)
{
    Point result = {0};

    for (size_t row = 0; row < getGridRowsCount(grid); row++)
    {
        for (size_t col = 0;  col < getGridColumnsCount(grid); col++)
        {
            if (!isCellBlocked(grid, row, col))
            {
                result.row=row;
                result.column=col;
                return result;
            }
        }
    }

    return result;
}

Output* solve(Grid* grid, const size_t movementPoints)
{
    size_t possibleMaxPath = movementPoints + 1;

    Output* output = (Output*)malloc(sizeof(Output));
    output->uniqueSquers = 0;
    output->path = (Point*)malloc(sizeof(Point)*possibleMaxPath);

    Point startingPoint = findFirstUnvisitedCell(grid);

    size_t counter = movementPoints;
    while(counter > 0)
    {
        Cell* currentCell = getGridCell(grid, startingPoint.row, startingPoint.column);
        setVisited(currentCell);
        counter--;
    }

    output->path[0] = startingPoint;
    return output;
}

#ifdef __cplusplus
}
#endif

#endif