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

    for (size_t i = 0; i < movementPoints; ++i)
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

    char* buffer = (char*)malloc(rows * cols);

    printf("Log 1 \n");

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

    printf("Log 2 \n");

    if (output)
    {
        for (size_t i = 0; i < output->pathLength; ++i)
        {
            Point p = output->path[i];

            buffer[p.row * cols + p.column] = '*';
        }

        printf("Log 3 \n");
        Point start = output->path[0];
        Point end = output->path[output->pathLength - 1];

        printf("Log 4 .row: %ld * cols: %ld + .cols: %ld \n", start.row, cols, start.column);
        printf("Log 4 index: %ld \n", start.row * cols + start.column);
        buffer[start.row * cols + start.column] = 'S';
        printf("Log 4.1 .row: %ld * cols: %ld + .cols: %ld \n", end.row, cols, end.column);
        printf("Log 4.1 index: %ld \n", end.row * cols + end.column);
        buffer[end.row * cols + end.column] = 'E';
    }
    printf("Log 5 \n");
    printf("\n");

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            printf("%c ", buffer[row * cols + col]);
        }

        printf("\n");
    }

    printf("Log 6 \n");
    printf("\n");

    free(buffer);
}

#ifdef __cplusplus
}
#endif

#endif