#ifndef CELL_H
#define CELL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint8_t Cell;

enum
{
    CellBlocked = 1 << 0,
    CellVisited = 1 << 1,
    CellInPath  = 1 << 2
};

static inline bool isBlocked(const Cell cell)
{
    return cell & CellBlocked;
}

static inline bool isVisited(const Cell cell)
{
    return cell & CellVisited;
}

static inline bool isInPath(const Cell cell)
{
    return cell & CellInPath;
}

static inline void setBlocked(Cell* cell)
{
    *cell |= CellBlocked;
}

static inline void setVisited(Cell* cell)
{
    *cell |= CellVisited;
}

static inline void setInPath(Cell* cell)
{
    *cell |= CellInPath;
}

Cell* createGridCells(const size_t rows, const size_t columns);
void destroyGridCells(Cell* cells);

#ifdef __cplusplus
}
#endif

#endif