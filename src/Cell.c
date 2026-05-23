#include "Cell.h"

Cell* createGridCells(const size_t rows, const size_t columns)
{
    const size_t cellsCount = rows * columns;
    Cell* cells = calloc(cellsCount, sizeof(*cells));

    return cells;
}

void destroyGridCells(Cell* cells)
{
    free(cells);
}