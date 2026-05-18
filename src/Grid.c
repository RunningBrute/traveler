#include "Grid.h"

typedef struct Grid
{
    size_t rows;
    size_t columns;
    Cell* cells;

} Grid;

Cell* createGridCells(size_t rows, size_t columns)
{
    size_t cellsCount = rows * columns;
    Cell* cells = (Cell*)calloc(cellsCount, sizeof(Cell));

    printf("Cells created. \n");

    return cells;
}

void destroyGridCells(Cell* cells)
{
    free(cells);

    printf("Cells destroyed.\n");
}

Grid* createGrid(size_t rows, size_t columns)
{
    Cell* cells = createGridCells(rows, columns);
    Grid* grid = malloc(sizeof(Grid));

    grid->rows = rows;
    grid->columns = columns;
    grid->cells = cells;

    printf("Grid created.\n");

    return grid;
}

void destroyGrid(Grid* grid)
{
    destroyGridCells(grid->cells);
    free(grid);

    printf("Grid destroyed.\n");
}