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

    cleanupSolvedOutput(result);
    destroyGrid(grid);
}