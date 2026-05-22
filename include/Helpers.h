#ifndef HELPERS_H
#define HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <math.h>

#include "Point.h"
#include "Grid.h"
#include "Solver.h"

static inline bool isValidStep(Point a, Point b)
{
    int dr = abs((int)a.row - (int)b.row);
    int dc = abs((int)a.column - (int)b.column);

    return (dr + dc) == 1;
}

static inline bool validatePath(const Grid* grid, const Output* output, size_t movementPoints)
{
    if (!grid || !output)
    {
        return false;
    }

    if (!output->path)
    {
        return false;
    }

    for (size_t i = 0; i < output->pathLength; ++i)
    {
        Point current = output->path[i];
        Point next = output->path[i + 1];

        if (!isValidStep(current, next))
        {
            return false;
        }

        if (isCellBlocked(grid, next.row, next.column))
        {
            return false;
        }
    }

    return true;
}

//   LEGEND
// # = blocked
// . = free
// * = path
// S = start
// E = end
void printGridWithPath(const Grid* grid, const Output* output, size_t movementPoints)
{
    size_t rows = getGridRowsCount(grid);
    size_t cols = getGridColumnsCount(grid);

    char* buffer = (char*)malloc(sizeof(*buffer)*rows * cols);

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            if (isCellBlocked(grid, row, col))
            {
                buffer[row * cols + col] = '#';
            }
            else
            {
                buffer[row * cols + col] = '.';
            }
        }
    }

    if (output)
    {
        for (size_t i = 0; i < output->pathLength; ++i)
        {
            Point p = output->path[i];

            if (p.row >= rows || p.column >= cols)
            {
                continue;
            }

            buffer[p.row * cols + p.column] = '*';
        }

        Point start = output->path[0];
        Point end = output->path[output->pathLength - 1];

        buffer[start.row * cols + start.column] = 'S';
        buffer[end.row * cols + end.column] = 'E';
    }
    printf("\n");

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            printf("%c ", buffer[row * cols + col]);
        }

        printf("\n");
    }

    printf("\n");

    free(buffer);
}

#ifdef __cplusplus
}
#endif

#endif