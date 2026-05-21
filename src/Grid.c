#include "Grid.h"

typedef struct Grid
{
    size_t rows;
    size_t columns;
    Cell* cells;
} Grid;

static inline size_t cellIndex(const Grid* grid, const size_t row, const size_t column)
{
    return row * grid->columns + column;
}

static void fillBlockedCells(Grid* grid, const Point* blockedSquers, const size_t blockedSquersCount)
{
    for (size_t i = 0; i < blockedSquersCount; i++)
    {
        const size_t index = cellIndex(grid, blockedSquers[i].row, blockedSquers[i].column);
        setBlocked(&grid->cells[index]);
    }
}

Grid* createGrid(const size_t rows, const size_t columns, const Point* blockedSquers, const size_t blockedSquersCount)
{
    if (rows == 0 || columns == 0)
        return NULL;

    Cell* cells = createGridCells(rows, columns);
    Grid* grid = malloc(sizeof(*grid));

    grid->rows = rows;
    grid->columns = columns;
    grid->cells = cells;

    fillBlockedCells(grid, blockedSquers, blockedSquersCount);

    printf("Grid created.\n");

    return grid;
}

Cell* getGridCell(Grid* grid, const size_t row, const size_t column)
{
    const size_t index = cellIndex(grid, row, column);
    return &grid->cells[index];
}

size_t getGridRowsCount(const Grid* grid)
{
    return grid->rows;
}

size_t getGridColumnsCount(const Grid* grid)
{
    return grid->columns;
}

bool isCellBlocked(const Grid* grid, const size_t row, const size_t column)
{
    const size_t index = cellIndex(grid, row, column);
    return isBlocked(grid->cells[index]);
}

bool isCellVisited(const Grid* grid, const size_t row, const size_t column)
{
    const size_t index = cellIndex(grid, row, column);
    return isVisited(grid->cells[index]);
}

void destroyGrid(Grid* grid)
{
    if (grid) destroyGridCells(grid->cells);
    free(grid);

    printf("Grid destroyed.\n");
}