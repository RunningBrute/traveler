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
    size_t pathLength;
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
        return -100;
    if(isCellVisited(grid, row, column))
        return 10;

    return 100;
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

Point* findBestStartingCell(const Grid* grid)
{
    const size_t maxRows = getGridRowsCount(grid);
    const size_t maxCols = getGridColumnsCount(grid);
    const size_t bufferSize = maxRows*maxCols;
    size_t bestScore = 0;
    Point* result = (Point*)malloc(sizeof(*result));

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
                result->row = row;
                result->column = col;
            }
        }
    }

    return NULL;
}

Point* findFirstUnvisitedCell(const Grid* grid)
{
    Point* result = (Point*)malloc(sizeof(*result));

    for (size_t row = 0; row < getGridRowsCount(grid); row++)
    {
        for (size_t col = 0;  col < getGridColumnsCount(grid); col++)
        {
            if (!isCellBlocked(grid, row, col))
            {
                result->row=row;
                result->column=col;
                return result;
            }
        }
    }

    return NULL;
}

typedef Point* (*StartingPointStrategy)(const Grid* grid);

Output* solve(Grid* grid, const size_t movementPoints, StartingPointStrategy startingPointStrategy)
{
    if (!grid)
        return NULL;

    size_t possibleMaxPath = movementPoints + 1;

    Output* output = (Output*)malloc(sizeof(*output));
    output->uniqueSquers = 0;
    output->path = (Point*)malloc(sizeof(*output->path)*possibleMaxPath);
    output->pathLength = 0;

    //for (size_t i = 0; i < possibleMaxPath; i++)
    //{
    //    output->path[i].column = 0;
    //    output->path[i].row = 0;
    //}

    Point* startingPoint = startingPointStrategy(grid);
    if (!startingPoint)
        return NULL;

    Point currentPoint;
    currentPoint.column = startingPoint->column;
    currentPoint.row = startingPoint->row;

    printf("Starting point added to path! Row: %ld, Col: %ld \n", currentPoint.row, currentPoint.column);
    output->path[0] = currentPoint;
    output->pathLength++;
    output->uniqueSquers++;

    size_t pointsInPath = 1;
    size_t counter = movementPoints;
    while(counter > 0)
    {
        Cell* currentCell = getGridCell(grid, currentPoint.row, currentPoint.column);
        setVisited(currentCell);

        int bestScore = 0;
        Point bestPoint = {
            .row = 0,
            .column = 0
        };

        int bestVisitedScore = 0;
        Point bestVisitedPoint = {
            .row = 0,
            .column = 0
        };

        if (!isCellBlocked(grid, currentPoint.row + 1, currentPoint.column))
        {   
            int north = get3x3WindowScore(grid, currentPoint.row + 1, currentPoint.column);
            if (north > bestScore)
            {
                if (!isCellVisited(grid, currentPoint.row + 1, currentPoint.column))
                {
                    bestScore = north;
                    bestPoint.row = currentPoint.row + 1,
                    bestPoint.column = currentPoint.column;
                }
                else
                {
                    bestVisitedScore = north;
                    bestVisitedPoint.row = currentPoint.row + 1,
                    bestVisitedPoint.column = currentPoint.column;
                }
                printf("Check north Row: %ld, Col: %ld \n", currentPoint.row + 1, currentPoint.column);
            }
        }

        if (!isCellBlocked(grid, currentPoint.row - 1, currentPoint.column))
        {
            int south = get3x3WindowScore(grid, currentPoint.row - 1, currentPoint.column);
            if (south > bestScore)
            {
                if (!isCellVisited(grid, currentPoint.row - 1, currentPoint.column))
                {
                    bestScore = south;
                    bestPoint.row = currentPoint.row - 1,
                    bestPoint.column = currentPoint.column;
                }
                else
                {
                    bestVisitedScore = south;
                    bestVisitedPoint.row = currentPoint.row - 1,
                    bestVisitedPoint.column = currentPoint.column;
                }
                printf("Check south Row: %ld, Col: %ld \n", currentPoint.row - 1, currentPoint.column);
            }
        }

        if (!isCellBlocked(grid, currentPoint.row, currentPoint.column - 1))
        {
            int west = get3x3WindowScore(grid, currentPoint.row, currentPoint.column - 1);
            if (west > bestScore)
            {
                if (!isCellVisited(grid, currentPoint.row, currentPoint.column - 1))
                {
                    bestScore = west;
                    bestPoint.row = currentPoint.row,
                    bestPoint.column = currentPoint.column - 1;
                }
                else
                {
                    bestVisitedScore = west;
                    bestVisitedPoint.row = currentPoint.row,
                    bestVisitedPoint.column = currentPoint.column - 1;
                }
                printf("Check west Row: %ld, Col: %ld \n", currentPoint.row, currentPoint.column - 1);
            }
        }

        if (!isCellBlocked(grid, currentPoint.row, currentPoint.column + 1))
        {
            int east = get3x3WindowScore(grid, currentPoint.row, currentPoint.column + 1);
            if (east > bestScore)
            {
                if (!isCellVisited(grid, currentPoint.row, currentPoint.column + 1))
                {
                    bestScore = east;
                    bestPoint.row = currentPoint.row,
                    bestPoint.column = currentPoint.column + 1;
                }
                else
                {
                    bestVisitedScore = east;
                    bestVisitedPoint.row = currentPoint.row,
                    bestVisitedPoint.column = currentPoint.column + 1;
                }
                printf("Check east Row: %ld, Col: %ld \n", currentPoint.row, currentPoint.column + 1);
            }
        }

        if (bestScore == 0 && bestVisitedScore == 0)
        {
            printf("DEAD END! GAME OVER \n");
            break;
        }

        if (bestScore > 0)
        {
            printf("New new point added to path! Row: %ld, Col: %ld \n", bestPoint.row, bestPoint.column);
            currentPoint = bestPoint;
            output->path[pointsInPath] = bestPoint;
            output->pathLength++;
            pointsInPath++;
        }
        else if (bestVisitedScore > 0)
        {
            printf("New visited point added to path! Row: %ld, Col: %ld \n", bestVisitedPoint.row, bestVisitedPoint.column);
            currentPoint = bestVisitedPoint;
            output->path[pointsInPath] = bestVisitedPoint;
            output->pathLength++;
            pointsInPath++;
        }
        else
        {
            printf("nothing added \n");
        }

        if (!isCellVisited(grid, currentPoint.row, currentPoint.column))
        {
            output->uniqueSquers++;
        }

        counter--;
    }

    return output;
}

void cleanupSolvedOutput(Output* output)
{
    if (output) free(output->path);
    free(output);
}

#ifdef __cplusplus
}
#endif

#endif