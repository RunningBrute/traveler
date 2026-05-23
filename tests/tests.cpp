#include <catch2/catch_test_macros.hpp>

#include <math.h>

#include "Grid.h"
#include "Point.h"
#include "Solver.h"
#include "Helpers.h"

TEST_CASE("No grid, no solution")
{
    const size_t movementPoints = 1;
    const size_t rows = 0;
    const size_t cols = 0;
    const Point blockedSquers[] = {};
    const size_t blockedSquesrCount = 0;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    REQUIRE(grid == NULL);
    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a point so at least we can start")
{
    const size_t movementPoints = 1;
    const size_t rows = 1;
    const size_t cols = 1;
    const Point blockedSquers[] = {};
    const size_t blockedSquesrCount = 0;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result->pathLength == 1);
    REQUIRE(result->path[0].row == 0);
    REQUIRE(result->path[0].column == 0);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a point, but blocked, so we cant start")
{
    const size_t movementPoints = 1;
    const size_t rows = 1;
    const size_t cols = 1;
    const Point blockedSquers[] = {{0, 0}};
    const size_t blockedSquesrCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid is a true grid, but all cells are blocked, so we cant start again")
{
    const size_t movementPoints = 1;
    const size_t rows = 2;
    const size_t cols = 2;
    const Point blockedSquers[] = {{0,0},{0,1},{1,0},{1,1}};
    const size_t blockedSquesrCount = 4;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result == NULL);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Two cells available so both should be added into path")
{
    const size_t movementPoints = 1;
    const size_t rows = 2;
    const size_t cols = 2;
    const Point blockedSquers[] = {{0,0},{0,1}};
    const size_t blockedSquesrCount = 2;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    validatePath(grid, result, movementPoints);
    REQUIRE(result->pathLength == 2);
    REQUIRE(result->path[0].row == 1);
    REQUIRE(result->path[0].column == 0);
    REQUIRE(result->path[1].row == 1);
    REQUIRE(result->path[1].column == 1);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Grid like a stick but should be ok")
{
    const size_t movementPoints = 5;
    const size_t rows = 8;
    const size_t cols = 1;
    const Point blockedSquers[] = {{0,0}};
    const size_t blockedSquesrCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);
    validatePath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Revisit is possible - we should end when we started")
{
    const size_t movementPoints = 12;
    const size_t rows = 8;
    const size_t cols = 1;
    const Point blockedSquers[] = {{0,0}};
    const size_t blockedSquesrCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    REQUIRE(result->pathLength == movementPoints + 1); // starting point also count

    printGridWithPath(grid, result, movementPoints);
    validatePath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Corridor test")
{
    const size_t movementPoints = 3;
    const size_t rows = 3;
    const size_t cols = 5;
    const Point blockedSquers[] = {
        {0,0}, {0,1}, {0,2}, {0,3}, {0,4},
                                    {1,4},
        {2,0}, {2,1}, {2,2}, {2,3}, {2,4}
    };
    const size_t blockedSquesrCount = sizeof(blockedSquers)/sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);
    validatePath(grid, result, movementPoints);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Check the perimeter!")
{
    const size_t movementPoints = 14;
    const size_t rows = 4;
    const size_t cols = 5;
    const Point blockedSquers[] = {
        {1,1}, {1,2}, {1,3},
        {2,1}, {2,2}, {2,3}
    };
    const size_t blockedSquesrCount = sizeof(blockedSquers)/sizeof(blockedSquers[0]);

    Grid* grid = createGrid(rows, cols, blockedSquers, blockedSquesrCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);
    validatePath(grid, result, movementPoints);

    // starting point is the same as ending point
    // so we have only result->pathLength - 1 unique squers
    REQUIRE(result->pathLength - 1 == result->uniqueSquers);
    REQUIRE(result->uniqueSquers == movementPoints);
    
    Point start = result->path[0];
    Point end = result->path[result->pathLength - 1];

    REQUIRE(start.row == end.row);
    REQUIRE(start.column == end.column);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}

TEST_CASE("Solver should avoid bouncing")
{
    const size_t movementPoints = 5;
    const size_t rows = 2;
    const size_t cols = 3;
    const Point blockedSquares[] = {{1,1}};
    const size_t blockedSquaresCount = 1;

    Grid* grid = createGrid(rows, cols, blockedSquares, blockedSquaresCount);
    Output* result = solve(grid, movementPoints, findFirstUnvisitedCell);

    printGridWithPath(grid, result, movementPoints);

    REQUIRE(result != NULL);
    REQUIRE(validatePath(grid, result, movementPoints));
    //REQUIRE(result->uniqueSquers == 3);

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}