#include "Cell.h"

Cell* createGridCells(const size_t rows, const size_t columns)
{
    const size_t cellsCount = rows * columns;
    Cell* cells = (Cell*)calloc(cellsCount, sizeof(Cell));

    printf("Cells created. \n");

    return cells;
}

void destroyGridCells(Cell* cells)
{
    free(cells);

    printf("Cells destroyed.\n");
}