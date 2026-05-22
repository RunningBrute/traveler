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

Point findBestStartingCell(const Grid* grid);
Point findFirstUnvisitedCell(const Grid* grid);

typedef Point (*StartingPointStrategy)(const Grid* grid);

typedef struct Candidate
{
    int score;
    Point point;
} Candidate;

Output* solve(Grid* grid, const size_t movementPoints, StartingPointStrategy startingPointStrategy);
void cleanupSolvedOutput(Output* output);

#ifdef __cplusplus
}
#endif

#endif