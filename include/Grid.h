#ifndef GRID_H
#define GRID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Cell.h"
#include "Point.h"

typedef struct Grid Grid;

Grid* createGrid(const size_t rows, const size_t columns, const Point* blockedSquers, const size_t blockedSquersCount);
bool isCellBlocked(const Grid* grid, const size_t row, const size_t column);
void destroyGrid(Grid* grid);

#ifdef __cplusplus
}
#endif

#endif