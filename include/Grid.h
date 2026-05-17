#ifndef GRID_H
#define GRID_H

#include <stdint.h>

typedef uint8_t Cell;

typedef struct Grid
{
    int rows;
    int columns;
    Cell* cells;

} Grid;

#endif