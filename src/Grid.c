#include "Grid.h"

typedef struct Grid
{
    size_t rows;
    size_t columns;
    Cell* cells;
} Grid;

static inline size_t cellIndex(const Grid* grid, const Point point)
{
    return point.row * grid->columns + point.column;
}

static void fillBlockedCells(Grid* grid, const Point* blockedSquers, const size_t blockedSquersCount)
{
    for (size_t i = 0; i < blockedSquersCount; i++)
    {
        const size_t index = cellIndex(grid, blockedSquers[i]);
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

    return grid;
}

Cell* getGridCell(Grid* grid, const Point point)
{
    const size_t index = cellIndex(grid, point);
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

bool isPointInsideGrid(const Grid* grid, const Point point)
{
    return point.row >= 0 && point.column >= 0 && point.row < getGridRowsCount(grid) && point.column < getGridColumnsCount(grid);
}

bool isCellBlocked(const Grid* grid, const Point point)
{
    const size_t index = cellIndex(grid, point);
    return isBlocked(grid->cells[index]);
}

bool isCellVisited(const Grid* grid, const Point point)
{
    const size_t index = cellIndex(grid, point);
    return isVisited(grid->cells[index]);
}

void destroyGrid(Grid* grid)
{
    if (grid) destroyGridCells(grid->cells);
    free(grid);
}