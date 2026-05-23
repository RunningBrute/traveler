#ifndef POINTS_H
#define POINTS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Point
{
    int row;
    int column;
} Point;

static inline bool pointsEqual(const Point a, const Point b)
{
    return a.row == b.row && a.column == b.column;
}

#ifdef __cplusplus
}
#endif

#endif