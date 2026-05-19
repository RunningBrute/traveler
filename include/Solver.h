#ifndef SOLVER_H
#define SOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Grid.h"
#include "Point.h"

typedef struct Output
{
    Point* path;
    size_t uniqueSquers;
} Output;

Output* solve(Grid* grid, const size_t movementPoints)
{
    return NULL;
}

#ifdef __cplusplus
}
#endif

#endif