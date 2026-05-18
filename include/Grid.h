#ifndef GRID_H
#define GRID_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


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

static inline void setBlocked(Cell cell)
{
    cell |= CellBlocked;
}

static inline void setVisited(Cell cell)
{
    cell |= CellVisited;
}

static inline void setInPath(Cell cell)
{
    cell |= CellInPath;
}

typedef struct Grid
{
    size_t rows;
    size_t columns;
    Cell* cells;

} Grid;

Cell* createGridCells(size_t rows, size_t columns)
{
    size_t cellsCount = rows * columns;
    return (Cell*)calloc(cellsCount, sizeof(Cell));
}

void destroyGridCells(Cell* cells)
{
    free(cells);
}

Grid* createGrid(size_t rows, size_t columns)
{
    Grid grid;
    grid.rows = rows;
    grid.columns = columns;
    grid.cells = createGridCells(rows, columns);
}

void destroyGrid(Grid* grid)
{
    destroyGridCells(grid->cells);
    free(grid);
}

#endif