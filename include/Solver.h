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

static inline bool rowInRange(size_t row, size_t max){ return row > 0 && row < max; }
static inline bool columnInRange(size_t col, size_t max){ return col > 0 && col < max; }

int getNeighbourScore(const Grid* grid, const size_t row, const size_t column)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);

    if(!rowInRange(row, maxRows) || !columnInRange(column, maxCols))
        return 0;
    if(isCellBlocked(grid, row, column))
        return -1;

    return 5;
}

int get3x3WindowScore(const Grid* grid, const size_t row, const size_t column)
{
    int score = 0;

    score += getNeighbourScore(grid, row - 1, column - 1);
    score += getNeighbourScore(grid, row - 1, column    );
    score += getNeighbourScore(grid, row - 1, column + 1);
    score += getNeighbourScore(grid, row,     column - 1);
    score += getNeighbourScore(grid, row,     column + 1);
    score += getNeighbourScore(grid, row + 1, column - 1);
    score += getNeighbourScore(grid, row + 1, column    );
    score += getNeighbourScore(grid, row + 1, column + 1);

    return score;
}

Point findBestStartingCell(const Grid* grid)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);
    const size_t bufferSize = maxRows*maxCols;
    size_t bestScore = 0;
    Point result = {0};

    int* bestNeighboringScoreMap = (int*)malloc(sizeof(*bestNeighboringScoreMap)*bufferSize);

    for (size_t row = 0; row < maxRows; row++)
    {
        for (size_t col = 0;  col < maxCols; col++)
        {
            if (isCellBlocked(grid, row, col))
                continue;

            const int score = get3x3WindowScore(grid, row, col);
            if (score > bestScore)
            {
                bestScore = score;
                result.row = row;
                result.column = col;
            }
        }
    }

    return result;
}

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

typedef Point (*StartingPointStrategy)(const Grid* grid);

Output* solve(Grid* grid, const size_t movementPoints, StartingPointStrategy startingPointStrategy)
{
    size_t possibleMaxPath = movementPoints + 1;

    Output* output = (Output*)malloc(sizeof(*output));
    output->uniqueSquers = 0;
    output->path = (Point*)malloc(sizeof(*output->path)*possibleMaxPath);

    Point startingPoint = startingPointStrategy(grid);

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